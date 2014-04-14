#include "parser.h"

void parse(char *buf){
	lexer_capture(buf);
	context = CT_REGULAR;
	g_control();
}

token_t match(int c){
	token_t result;
	if ( lexer_current_tok.type == c){
		result.type = lexer_current_tok.type;
		if(c == tID){
			result.str = (char*)malloc(strlen(lexer_current_tok.str)+1);
			strcpy(result.str, lexer_current_tok.str);
		}else if(c == tNUMBER){
			result.num = lexer_current_tok.num;
		}
		lexer_get_tok();
		return result;
	}
	print_syntax_error(lexer_current_tok.type,current_p-1,buffer);
	avrsh_error();
}

int g_control() {
	if ( lexer_current_tok.type == 0){
		lexer_get_tok();
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
	g_control();
}

int g_statement(){
	token_t ident = match(tID);

	avrsh_function_t *maybe_fun = avrsh_ftable_find(ident.str);
	if(maybe_fun == NULL){
		print_unk_fun_error(current_p-1, ident.str, buffer);
		avrsh_error();
	}

	int argc = 1;
	char **argv = (char**)malloc(sizeof(char*));
	argv[0] = (char*)malloc(strlen(ident.str)+1);
	strcpy(argv[0], ident.str);
	g_args(&argc,argv);

	match(tDELIM);

	int i;
	for(i = 0; i < argc; i++){
		free(argv[i]);
		free(argv);
	}
}

int g_args(int *argc, char **argv){
	if ( lexer_current_tok.type == 0){
		lexer_get_tok();
	}

	char *arg;
	switch(lexer_current_tok.type) {
		case tDOLL:
			arg = g_get();

			argv = (char**)realloc(argv,(*argc+1) * sizeof(char**));
			argv[*argc] = (char*)malloc(strlen(arg));
			*argc++;
			g_args(argc,argv);
			break;
		case tLP:
			g_eval();
			g_args(argc,argv);
			break;
		case tDELIM:
			return;
			break;
		default:
			print_syntax_error(lexer_current_tok.type, current_p, buffer);
			avrsh_error();
	}
}

int g_ifst(){
	match(tIF);
	g_eval();
	g_branch();
}

int g_branch(){
	g_control();
	g_maybe_branch();
}

int g_maybe_branch(){
	switch(lexer_current_tok.type) {
		case tELSE:
			match(tELSE);
			g_control();
			match(tEND);
			break;
		case tELIF:
			match(tELIF);
			g_eval();
			g_branch();
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
	g_eval();
	g_control();
	match(tEND);
}

int g_set(){
	match(tSET);
	match(tID);
	match(tEQ);
	match(tID);
	match(tDELIM);
}

char *g_get(){
	match(tDOLL);
	token_t value = match(tID);
	char *strval = (char*)malloc(strlen(value.str));
	strcpy(strval,value.str);
	free(value.str);

	return strval;
}

float g_getf(){
	match(tSHAR);
	match(tID);
}

char *g_eval(){
	match(tLP);
	context = CT_EVAL;
	g_op();
	g_aexprorv();
	context = CT_REGULAR;
	match(tRP);
}

int _is_operator_numeric_only(int tok){
	switch(tok) {
		case tOP_PLUS:
		case tOP_MINUS:
		case tOP_TIMES:
		case tOP_DIV:
		case tOP_MOD:
			return 1;
		default:
			return 0;
	}
}

char *g_aexprorv(token_t *left){
	token_t right;
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
		default:
			print_syntax_error(lexer_current_tok.type, current_p, buffer);
			avrsh_error();
	}
	token_t operator = match(lexer_current_tok.type);
	right = g_op();
	if(_is_operator_numeric_only(operator.type) && (left->type != tNUMBER || right.type != tNUMBER) ){
		print_type_mism_error(current_p-1, operator.str, buffer);
		avrsh_error();
	}
}

token_t g_op(){
	token_t result;
	switch(lexer_current_tok.type) {
		case tDOLL:
			result.str = g_get();
			result.type = tID;
			break;
		case tSHAR:
			result.num = g_getf();
			result.type = tNUMBER;
			break;
		case tNUMBER:
			result.num = match(tNUMBER).num;
			break;
		case tSQUOTE:
			match(tSQUOTE);
			result.str = match(tID).str;
			match(tSQUOTE);
			result.type = tID;
			break;
		default:
			print_syntax_error(lexer_current_tok.type, current_p, buffer);
			avrsh_error();
	}
	return result;
}

