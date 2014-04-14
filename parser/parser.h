#ifndef PARSER_H
#define PARSER_H
#include "tab.h"
#include "lexer.h"
#include "printer.h"
#include "avrsh.h"
#include "tree_t.h"

typedef enum {
	CT_REGULAR,CT_EVAL
} Context;

Context context;


void parse(char *buf);

token_t match(int);

int g_control();
int g_statement();
int g_args(int *argc, char **argv);
int g_ifst();
int g_branch();
int g_maybe_branch();
int g_loop();
int g_set();
char* g_get();
float g_getf();
char *g_eval();
char *g_aexprorv();
token_t g_op();
#endif
