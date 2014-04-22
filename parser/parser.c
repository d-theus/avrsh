#include "parser.h"

void parse(char *buf){
	lexer_capture(buf);
	g_control(0);
}

token_t match(int c){
	token_t result;
	int len;
	if ( lexer_current_tok.type == c){
		result.type = lexer_current_tok.type;
		result.pos = lexer_current_tok.pos;
		switch(c){
			case tID:
				result.val.str = strdup(lexer_current_tok.val.str);
				break;
			case tNUMBER:
				result.val.num = lexer_current_tok.val.num;
				break;
			case tOP_PLUS:
			case tOP_MINUS:
			case tOP_TIMES:
			case tOP_DIV:
			case tOP_MOD:
			case tOP_GT:
			case tOP_LT:
			case tOP_GEQ:
			case tOP_LEQ:
			case tOP_EQ:
			case tOP_NEQ:
				strcpy(result.val.opr.str, lexer_current_tok.val.opr.str);
				result.val.opr.fun_n = lexer_current_tok.val.opr.fun_n;
				result.val.opr.fun_s = lexer_current_tok.val.opr.fun_s;
				break;
		}
		lexer_get_tok();
		return result;
	}
	print_syntax_error(lexer_current_tok.type,lexer_current_tok.pos - 1,buffer);
	avrsh_error();
}

int g_control(int fallthrough) {
	if ( lexer_current_tok.type == 0){
		lexer_get_tok();
	}
	if(fallthrough){
		while(1){
			switch( lexer_current_tok.type ){
				case tEOF:case tEND:case tELSE:case tELIF:
					return 0;
				default:
					lexer_get_tok();
			}
		}
	}
	switch( lexer_current_tok.type ) {
		case tID:
			g_statement();
			break;
		case tIF:
			g_ifst();
			break;
		case tWHILE:
			g_loop();
			break;
		case tSET:
			g_set();
			break;
		case tEOF:case tEND:case tELSE:case tELIF:
			return 0;
		default:
			print_syntax_error(lexer_current_tok.type, current_p, buffer);
			avrsh_error();
	}
	g_control(fallthrough);
}

int g_statement(){
	token_t ident = match(tID);

	avrsh_function_t *maybe_fun = avrsh_ftable_find(ident.val.str);
	if(maybe_fun == NULL){
		print_unk_fun_error(current_p-1, ident.val.str, buffer);
		avrsh_error();
	}

	int argc = 1;
	char **argv = (char**)malloc(sizeof(char*));
	argv[0] = strdup(ident.val.str);
	g_args(&argc,argv);

	match(tDELIM);

	maybe_fun->func(argc,argv);

	int i;
	for(i = 0; i < argc; i++){
		free(argv[i]);
	}
	free(argv);
	free(ident.val.str);
}

int g_args(int *argc, char **argv){
	if ( lexer_current_tok.type == 0){
		lexer_get_tok();
	}

	char *arg;
	switch(lexer_current_tok.type) {
		case tDOLL:
			arg = g_get();
			break;
		case tLP:
			arg = g_eval();
			break;
		case tID:
			arg = match(tID).val.str;
			break;
		case tDELIM:
			return;
			break;
		default:
			print_syntax_error(lexer_current_tok.type, current_p, buffer);
			avrsh_error();
	}
	int c = *argc;
	char **tmp = (char**)realloc(argv,(c+1) * sizeof(char*));
	if (tmp != NULL)
		argv = tmp;
	argv[c] = strdup(arg);
	(*argc)++;
	g_args(argc,argv);
	free(arg);
}

int _eval_logic(const char *a){
	if(strlen(a) == 0)
		return 0;
	if(strcmp(a,"f") == 0)
		return 0;
	if(strcmp(a,"false") == 0)
		return 0;
	if(strcmp(a,"0") == 0)
		return 0;
	return 1;
}

int g_ifst(){
	match(tIF);
	char *log = g_eval();
	int fallthrough = !_eval_logic(log);
	g_branch(fallthrough);
}

int g_branch(int fallthrough){
	g_control(fallthrough);
	fallthrough = !fallthrough;
	g_maybe_branch(fallthrough);
}

int g_maybe_branch(int fallthrough){
	switch(lexer_current_tok.type) {
		case tELSE:
			match(tELSE);
			g_control(fallthrough);
			match(tEND);
			break;
		case tELIF:
			match(tELIF);
			char *log = g_eval();
			fallthrough = !_eval_logic(log);
			g_branch(fallthrough);
			break;
		case tEND:
			match(tEND);
			break;
		default:
			print_syntax_error(lexer_current_tok.type, current_p, buffer);
			avrsh_error();
	}

}

int g_loop(){
	match(tWHILE);
	avrsh_str_t log;
	int fallthrough;
	int begin_p = current_p;
	char begin_c = current_c;
	token_t begin_tok = lexer_current_tok;
iter:
	log = g_eval();
	fallthrough = !_eval_logic(log);
	g_control(fallthrough);
	match(tEND);

	if(fallthrough == 0) {
		free(log);
		current_c = begin_c;
		current_p = begin_p;
		lexer_current_tok = begin_tok;
		goto iter;
	}
}

int g_set(){
	match(tSET);
	token_t ident = match(tID);
	match(tEQ);
	token_t rval;
	switch(lexer_current_tok.type) {
		case tID:
			rval = match(tID);
			break;
		case tNUMBER:
			rval = match(tNUMBER);
			break;
		case tLP:
			rval.type = tID;
			rval.val.str = g_eval();
			break;
		default:
			print_syntax_error(lexer_current_tok.type,lexer_current_tok.pos,buffer);
			avrsh_error();
	}
	match(tDELIM);
	if(rval.type == tID){
		avrsh_vtable_insert(ident.val.str, rval.val.str);
	} else {
		char *nums = (char*)malloc(32);
		itoa(rval.val.num,nums,10);
		avrsh_vtable_insert(ident.val.str, nums);
		free(nums);
	}
	free(ident.val.str);
	if(rval.type == tID){
		free(rval.val.str);
	}
}

char *g_get(){
	match(tDOLL);
	token_t ident = match(tID);

	avrsh_variable_t *var = NULL;
	var = avrsh_vtable_find(ident.val.str);
	if( var == NULL){
		print_und_var_error(ident.pos, ident.val.str, buffer);
		avrsh_error();
	}

	char *strval = strdup(var->value);
	free(ident.val.str);
	return strval;
}

avrsh_num_t g_getn(){
	match(tSHAR);

	token_t ident;
	ident = match(tID);

	avrsh_variable_t *var = NULL;
	var = avrsh_vtable_find(ident.val.str);

	if( var == NULL){
		print_und_var_error(ident.pos, ident.val.str, buffer);
		avrsh_error();
	}

	free(ident.val.str);
	return atoi(var->value);
}

char *g_eval(){
	match(tLP);
	token_t left = g_op();
	char * result = g_aexprorv(&left);
	match(tRP);
	return  result;
}

char *g_aexprorv(token_t *left){
	char *result;
	switch(lexer_current_tok.type) {
		case tOP_PLUS:
		case tOP_MINUS:
		case tOP_TIMES:
		case tOP_MOD:
		case tOP_DIV:
		case tOP_GT:
		case tOP_LT:
		case tOP_GEQ:
		case tOP_LEQ:
		case tOP_EQ:
		case tOP_NEQ:
		break;
		case tRP:
		if(left->type == tID){
			return left->val.str;
		}
		if(left->type == tNUMBER){
			avrsh_str_t numstr = (avrsh_str_t)malloc(32);
			itoa(left->val.num,numstr,10);
			return numstr;
		}
		default:
			print_syntax_error(lexer_current_tok.type, current_p, buffer);
			avrsh_error();
	}

	token_t right;
	token_t opr = match(lexer_current_tok.type);
	right = g_op();

	//numeric-only opr on nans
	if(opr.val.opr.fun_s == NULL && (left->type != tNUMBER || right.type != tNUMBER) ){ 
		print_type_mism_error(current_p-1, opr.val.opr.str, buffer);
		avrsh_error();
	}
	//different arg types
	if( left->type != right.type ){
		print_type_mism_error(current_p-1, opr.val.opr.str, buffer);
		avrsh_error();
	}

	if(left->type = tNUMBER){
		result = opr.val.opr.fun_n(left->val.num,right.val.num);
	} else {
		result = opr.val.opr.fun_s(left->val.str,right.val.str);
	}
}

token_t g_op(){
	token_t result;
	result.pos = lexer_current_tok.pos;
	switch(lexer_current_tok.type) {
		case tDOLL:
			result.val.str = g_get();
			result.type = tID;
			break;
		case tSHAR:
			result.val.num = g_getn();
			result.type = tNUMBER;
			break;
		case tNUMBER:
			result.val.num = match(tNUMBER).val.num;
			result.type = tNUMBER;
			break;
		case tSQUOTE:
			match(tSQUOTE);
			result.val.str = match(tID).val.str;
			match(tSQUOTE);
			result.type = tID;
			break;
		default:
			print_syntax_error(lexer_current_tok.type, current_p, buffer);
			avrsh_error();
	}
	return result;
}

