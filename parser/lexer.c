#include "lexer.h"
#include "printer.h"

#include "operations.c"

void _token_set_simple(int type){
	lexer_current_tok.type = type;
}

void _token_set_id(const char *val){
	lexer_current_tok.type = tID;
	lexer_current_tok.val.str = strdup(val);
}

void _token_set_num(){
	lexer_current_tok.type = tNUMBER;
}

void _token_set_opr(int type, const char *opstr,
		avrsh_str_t (*nf)(avrsh_num_t, avrsh_num_t),
		avrsh_str_t (*sf)(avrsh_str_t, avrsh_str_t)
		){
	lexer_current_tok.type = type;
	strcpy(lexer_current_tok.val.opr.str,opstr);
	lexer_current_tok.val.opr.fun_n = nf;
	lexer_current_tok.val.opr.fun_s = sf;
}

int lexer_capture(char *input){
	buffer = input;
	current_c = input[0];
	current_p = 0;
	return 0;
}

void skip(int c){
	current_p += c;
	current_c = buffer[current_p];
}

void advance() {
	skip(1);
}

token_t lexer_get_tok() {
	if(lexer_current_tok.type == tID && lexer_current_tok.val.str != NULL){
		free(lexer_current_tok.val.str);
		lexer_current_tok.val.str = NULL;
	}

	size_t len = strlen(buffer);
	if(current_p >= len){
		lexer_current_tok.type = tEOF;
		return lexer_current_tok;
	}
	while(isspace(current_c) && current_p < len) advance();

	lexer_current_tok.pos = current_p;

	//SIMPLE
	if(current_c == ';'){
		advance();
		_token_set_simple(tDELIM);
		return lexer_current_tok;
	}
	if(current_c == '$'){
		advance();
		_token_set_simple(tDOLL);
		return lexer_current_tok;
	}
	if(current_c == '#'){
		advance();
		_token_set_simple(tSHAR);
		return lexer_current_tok;
	}
	if(current_c == '('){
		advance();
		_token_set_simple(tLP);
		return lexer_current_tok;
	}
	if(current_c == ')'){
		advance();
		_token_set_simple(tRP);
		return lexer_current_tok;
	}
	if(current_c == '\''){
		advance();
		_token_set_simple(tSQUOTE);
		return lexer_current_tok;
	}
	//OPERATORS
	if(current_c == '<'){
		advance();
		if(current_c == '='){
			advance();
			_token_set_opr(tOP_LEQ,"<=",_op_leq_n,_op_leq_s);
			return lexer_current_tok;
		}
		_token_set_opr(tOP_LT, "<", _op_lt_n, _op_lt_s);
		return lexer_current_tok;
	}
	if(current_c == '>'){
		advance();
		if(current_c == '='){
			advance();
			_token_set_opr(tOP_GEQ,">=",_op_geq_n, _op_geq_s);
			return lexer_current_tok;
		}
		_token_set_opr(tOP_GT,"<", _op_gt_n, _op_gt_s);
		return lexer_current_tok;
	}
	if(current_c == '='){
		advance();
		if(current_c == '='){
			advance();
			_token_set_opr(tOP_EQ,"==",_op_eq_n, _op_eq_s);
			return lexer_current_tok;
		}
		_token_set_simple(tEQ);
		return lexer_current_tok;
	}
	if(current_c == '+'){
		advance();
		_token_set_opr(tOP_PLUS,"+",_op_plus,NULL);
		return lexer_current_tok;
	}
	if(current_c == '-'){
		advance();
		_token_set_opr(tOP_MINUS,"-", _op_minus,NULL);
		return lexer_current_tok;
	}
	if(current_c == '*'){
		advance();
		_token_set_opr(tOP_TIMES, "*",_op_times,NULL);
		return lexer_current_tok;
	}
	if(current_c == '/'){
		advance();
		_token_set_opr(tOP_DIV,"/",_op_div,NULL);
		return lexer_current_tok;
	}
	if(current_c == '%'){
		advance();
		_token_set_opr(tOP_MOD, "%", _op_mod,NULL);
		return lexer_current_tok;
	}
	if(current_c == '!'){
		advance();
		if(current_c == '='){
			advance();
			_token_set_opr(tOP_NEQ,"!=", _op_neq_n, _op_neq_s);
			return lexer_current_tok;
		}
		print_lexical_error(current_p-1, buffer);
		avrsh_error();
	}

	/* handling numbers */
	if(isdigit(current_c)){
		unsigned short begin = current_p;
		unsigned short end = current_p;

		do{
			advance();
			end ++;
		}while(isdigit(current_c));
		if(current_c == '.'){//floating point?
			print_lexical_error(current_p, buffer);
		}
		lexer_current_tok.type = tNUMBER;
		lexer_current_tok.val.num = atoi(&buffer[begin]);
		return lexer_current_tok;
	} //if number 

	/* handling word sequences */
	char word[64];
	unsigned char pos = 0;
	do{
		word[pos++] = current_c;
		advance();
	} while(isalnum(current_c) && pos < 64);
	word[pos] = '\0';

	if(0 == strcmp(word,"else")){
			lexer_current_tok.type = tELSE;
			return lexer_current_tok;
	}
	if(0 == strcmp(word,"elif")){
			lexer_current_tok.type = tELIF;
			return lexer_current_tok;
	}
	if(0 == strcmp(word,"end")){
			lexer_current_tok.type = tEND;
			return lexer_current_tok;
	}
	if(0 == strcmp(word,"if")){
			lexer_current_tok.type = tIF;
			return lexer_current_tok;
	}
	if(0 == strcmp(word,"set")){
			lexer_current_tok.type = tSET;
			return lexer_current_tok;
	}
	if(0 == strcmp(word,"while")){
			lexer_current_tok.type = tWHILE;
			return lexer_current_tok;
	}

	lexer_current_tok.type = tID;
	lexer_current_tok.val.str = strdup(word);
	return lexer_current_tok;
}
