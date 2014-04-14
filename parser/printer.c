#include "printer.h"

void print_tok(int tok){
	if(tok < 256){
		printf("%c", tok);
		return;
	}
	switch(tok) {
		case tCMD:
			printf("tCMD");
			break;
		case tDELIM:
			printf("tDELIM");
			break;
		case tELIF:
			printf("tELIF");
			break;
		case tELSE:
			printf("tELSE");
			break;
		case tEND:
			printf("tEND");
			break;
		case tDOLL:
			printf("tDOLL");
			break;
		case tID:
			printf("tID");
			break;
		case tIF:
			printf("tIF");
			break;
		case tNUMBER:
			printf("tNUMBER");
			break;
		case tSET:
			printf("tSET");
			break;
		case tWHILE:
			printf("tWHILE");
			break;
		case  tLP:
			printf("tLP");
			break;

		case  tRP:
			printf("tRP");
			break;
		case  tOP_PLUS:
			printf("tOP_PLUS");
			break;
		case  tOP_MINUS:
			printf("tOP_MINUS");
			break;
		case  tOP_TIMES:
			printf("tOP_TIMES");
			break;
		case  tOP_DIV:
			printf("tOP_DIV");
			break;
		case  tOP_MOD:
			printf("tOP_MOD");
			break;
		case  tOP_GT:
			printf("tOP_GT");
			break;
		case  tOP_LT:
			printf("tOP_LT");
			break;
		case  tOP_GEQ:
			printf("tOP_GEQ");
			break;
		case  tOP_LEQ:
			printf("tOP_LEQ");
			break;
		case  tOP_EQ:
			printf("tOP_EQ");
			break;
		case  tOP_NEQ:
			printf("tOP_NEQ");
			break;
		case  tEQ:
			printf("tEQ");
			break;
		case tSQUOTE:
			printf("tSQUOTE");
			break;
		default:
			printf("unknown");
	}
}

void print_pointer(char *input, int pos){
	printf("%s\n",input);
	int i = 0;
	for(;i<pos; i++){
		printf(" ");
	}
	printf("^\n");
}

void print_lexical_error(int pos, char *input){
	printf("Error at %d: unexpected character %c:\n", pos,input[pos]);
	print_pointer(input,pos);
}

void print_syntax_error(int tok, int pos, char *input){
	if (tok != tEOF){
		printf("Error at %d: unexpected token ");
		print_tok(tok);
		printf(":\n");
	} else {
		printf("Error: unexpected end of input\n");
	}
	print_pointer(input,pos);
}

void print_unk_fun_error(int pos, char *name, char *input){
	printf("Error: unknown function '%s'\n",name);
	print_pointer(input,pos);
}

void print_type_mism_error(int pos, char *op, char *input){
	printf("Error: type mismatch for operator %s:\n",op);
	print_pointer(input,pos);
}
