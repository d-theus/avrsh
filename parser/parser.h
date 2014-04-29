#ifndef PARSER_H
#define PARSER_H
#include "tab.h"
#include "lexer.h"
#include "printer.h"
#include "avrsh.h"



void parser_parse(char *buf);
jmp_buf end_of_parse;

token_t match(int);

int g_control(int);
int g_statement();
int g_args(int *argcp, char ***argvp);
int g_ifst();
int g_branch(int);
int g_maybe_branch(int);
int g_loop();
int g_set();
char* g_get();
avrsh_num_t g_getn();
char *g_eval();
char *g_aexprorv();
token_t g_op();
#endif
