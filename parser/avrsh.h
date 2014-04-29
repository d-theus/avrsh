#ifndef AVRSH_H
#define AVRSH_H
 
#include <stdlib.h>
#include <setjmp.h>

#include "tab.h"
#include "types.h"
#include "parser.h"

#include "uthash.h"

typedef struct avrsh_function_t {
	char *name;
	void (*func)(int, char**);
	UT_hash_handle hh;
} avrsh_function_t;

typedef struct avrsh_variable_t {
	char *name;
	char *value;
	UT_hash_handle hh;
} avrsh_variable_t;

avrsh_function_t *ftable;
avrsh_variable_t *vtable;

extern jmp_buf end_of_parse;

int (*avrsh_printf)(const char*, ...);
void (*avrsh_error)(void);

avrsh_function_t *avrsh_ftable_find(char *name);
avrsh_variable_t *avrsh_vtable_find(char *name);

void avrsh_ftable_insert(char *name, void (*f)(int,char**));
void avrsh_vtable_insert(char *name, char *value);

void avrsh_ftable_delete(char *name);
void avrsh_vtable_delete(char *name);

void avrsh_ftable_clear();
void avrsh_vtable_clear();

void avrsh_init();
void avrsh_set_printf_func(int (*f)(const char *fmt, ...));
void avrsh_set_handler_error(void (*f)(void));

#endif
