#include "lexer.h"
#include "printer.h"

#include "operations.c"

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
	if(lexer_current_tok.type == tID && lexer_current_tok.str != NULL){
		free(lexer_current_tok.str);
	}

	size_t len = strlen(buffer);
	if(current_p >= len){
		lexer_current_tok.type = tEOF;
		return lexer_current_tok;
	}
	while(isspace(current_c) && current_p < len) advance();
	if(current_c == ';'){
		advance();
		lexer_current_tok.type = tDELIM;
		return lexer_current_tok;
	}
	if(current_c == '$'){
		advance();
		lexer_current_tok.type = tDOLL;
		return lexer_current_tok;
	}
	if(current_c == '#'){
		advance();
		lexer_current_tok.type = tSHAR;
		return lexer_current_tok;
	}
	if(current_c == '('){
		advance();
		lexer_current_tok.type = tLP;
		return lexer_current_tok;
	}
	if(current_c == ')'){
		advance();
		lexer_current_tok.type = tRP;
		return lexer_current_tok;
	}
	if(current_c == '<'){
		advance();
		if(current_c == '='){
			advance();
			lexer_current_tok.type = tOP_LEQ;
			return lexer_current_tok;
		}
		lexer_current_tok.type = tOP_LT;
		return lexer_current_tok;
	}
	if(current_c == '>'){
		advance();
		if(current_c == '='){
			advance();
			lexer_current_tok.type = tOP_GEQ;
			return lexer_current_tok;
		}
		lexer_current_tok.type = tOP_GT;
		return lexer_current_tok;
	}
	if(current_c == '='){
		advance();
		if(current_c == '='){
			advance();
			lexer_current_tok.type = tOP_EQ;
			return lexer_current_tok;
		}
		lexer_current_tok.type = tEQ;
		return lexer_current_tok;
	}
	if(current_c == '+'){
		advance();
		lexer_current_tok.type = tOP_PLUS;
		return lexer_current_tok;
	}
	if(current_c == '-'){
		advance();
		lexer_current_tok.type = tOP_MINUS;
		return lexer_current_tok;
	}
	if(current_c == '*'){
		advance();
		lexer_current_tok.type = tOP_TIMES;
		return lexer_current_tok;
	}
	if(current_c == '/'){
		advance();
		lexer_current_tok.type = tOP_DIV;
		return lexer_current_tok;
	}
	if(current_c == '%'){
		advance();
		lexer_current_tok.type = tOP_MOD;
		return lexer_current_tok;
	}
	if(current_c == '!'){
		advance();
		if(current_c == '='){
			advance();
			lexer_current_tok.type = tOP_NEQ;
			return lexer_current_tok;
		}
		print_lexical_error(current_p-1, buffer);
		avrsh_error();
	}
	if(current_c == '\''){
		advance();
		lexer_current_tok.type = tSQUOTE;
		return lexer_current_tok;
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
			if( isdigit(buffer[current_p+1]) ){//ensure digit goes after .TODO:handle possible segfaults
				unsigned short fbegin = current_p;
				unsigned short fend = current_p;
				do{
					advance();
					fend ++;
				}while(isdigit(current_c));
			}
		}
		lexer_current_tok.type = tNUMBER;
		lexer_current_tok.num = atof(&buffer[begin]);
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
	lexer_current_tok.str = (avrsh_str_t)malloc(strlen(word)+1);
	strcpy(lexer_current_tok.str,word);
	return lexer_current_tok;
}
