#ifndef LEXER_H
#define LEXER_H
#include <ctype.h>
#include <string.h>
#include "tab.h"
#include "types.h"
#include "avrsh.h"

char current_c;
unsigned short current_p;

char *buffer;

void lexer_match(int tok);
int lexer_capture(char *);

token_t lexer_get_tok();

token_t lexer_current_tok;
#endif
