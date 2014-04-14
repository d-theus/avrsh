#ifndef PRINTER_H
#define PRINTER_H
#include <stdio.h>
#include <stdlib.h>
#include "tab.h"
#include "lexer.h"

void print_tok(int tok);

void print_syntax_error(int tok, int pos, char *input);
void print_lexical_error(int pos, char *input);
void print_unk_fun_error(int pos, char *name, char *input);
void print_type_mism_error(int pos, char *op, char *input);
#endif
