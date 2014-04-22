/*
 * This is table of tokens
 * for avrsh.
 */

#ifndef TAB_H
#define TAB_H 

#include "types.h"

#define  tCMD  		256
#define  tDELIM		257 
#define  tELIF		258 
#define  tELSE		259 
#define  tEND		260 
#define  tDOLL		261
#define  tSHAR		262
#define  tID		263 
#define  tIF		264 
#define  tNUMBER	265 
#define  tSET 		266 
#define  tWHILE		267 
#define  tEOF		-1

#define  tLP		268
#define  tRP		269

#define  tOP_PLUS	270
#define  tOP_MINUS	271
#define  tOP_TIMES	272
#define  tOP_DIV	273
#define  tOP_MOD	274
#define  tOP_GT		275
#define  tOP_LT		276
#define  tOP_GEQ	277
#define  tOP_LEQ	278
#define  tOP_EQ		279
#define  tOP_NEQ	280

#define  tEQ		281

#define tSQUOTE		282

typedef struct token_t {
	int type;
	int pos;
	union{
		avrsh_str_t str;
		avrsh_num_t num;
		avrsh_operator_t opr;
	} val;
} token_t;

#endif
