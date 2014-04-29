#include "printer.h"

void print_tok(int tok){
	if(tok < 256){
		avrsh_printf("%c", tok);
		return;
	}
	switch(tok) {
		case tCMD:
			avrsh_printf("tCMD");
			break;
		case tDELIM:
			avrsh_printf("tDELIM");
			break;
		case tELIF:
			avrsh_printf("tELIF");
			break;
		case tELSE:
			avrsh_printf("tELSE");
			break;
		case tEND:
			avrsh_printf("tEND");
			break;
		case tDOLL:
			avrsh_printf("tDOLL");
			break;
		case tID:
			avrsh_printf("tID");
			break;
		case tIF:
			avrsh_printf("tIF");
			break;
		case tNUMBER:
			avrsh_printf("tNUMBER");
			break;
		case tSET:
			avrsh_printf("tSET");
			break;
		case tWHILE:
			avrsh_printf("tWHILE");
			break;
		case  tLP:
			avrsh_printf("tLP");
			break;

		case  tRP:
			avrsh_printf("tRP");
			break;
		case  tOP_PLUS:
			avrsh_printf("tOP_PLUS");
			break;
		case  tOP_MINUS:
			avrsh_printf("tOP_MINUS");
			break;
		case  tOP_TIMES:
			avrsh_printf("tOP_TIMES");
			break;
		case  tOP_DIV:
			avrsh_printf("tOP_DIV");
			break;
		case  tOP_MOD:
			avrsh_printf("tOP_MOD");
			break;
		case  tOP_GT:
			avrsh_printf("tOP_GT");
			break;
		case  tOP_LT:
			avrsh_printf("tOP_LT");
			break;
		case  tOP_GEQ:
			avrsh_printf("tOP_GEQ");
			break;
		case  tOP_LEQ:
			avrsh_printf("tOP_LEQ");
			break;
		case  tOP_EQ:
			avrsh_printf("tOP_EQ");
			break;
		case  tOP_NEQ:
			avrsh_printf("tOP_NEQ");
			break;
		case  tEQ:
			avrsh_printf("tEQ");
			break;
		case tSQUOTE:
			avrsh_printf("tSQUOTE");
			break;
		default:
			avrsh_printf("unknown");
	}
}

void print_pointer(char *input, int pos){
	avrsh_printf("%s\n",input);
	int i = 0;
	for(;i<pos; i++){
		avrsh_printf(" ");
	}
	avrsh_printf("^\n");
}

void print_lexical_error(int pos, char *input){
	avrsh_printf("Error at %d: unexpected character %c:\n", pos,input[pos]);
	print_pointer(input,pos);
}

void print_syntax_error(int tok, int pos, char *input){
	if (tok != tEOF){
		avrsh_printf("Error at %d: unexpected token ");
		print_tok(tok);
		avrsh_printf(":\n");
	} else {
		avrsh_printf("Error: unexpected end of input\n");
	}
	print_pointer(input,pos);
}

void print_unk_fun_error(int pos, char *name, char *input){
	avrsh_printf("Error: unknown function '%s'\n",name);
	print_pointer(input,pos);
}

void print_und_var_error(int pos, char *name, char *input){
	avrsh_printf("Error: undefined variable '%s'\n",name);
	print_pointer(input,pos);
}

void print_type_mism_error(int pos, char *op, char *input){
	avrsh_printf("Error: type mismatch for operator %s:\n",op);
	print_pointer(input,pos);
}
