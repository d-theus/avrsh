#ifndef TYPES_H
#define TYPES_H


typedef char* avrsh_str_t;
typedef int avrsh_num_t;
typedef struct _op_t{
	char str[3];
	union {
		char *(*fun_f)(avrsh_num_t a, avrsh_num_t b);
		char *(*fun_s)(char *a,char *b);
	};
} avrsh_operator_t;

#endif
