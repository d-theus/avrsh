#ifndef TYPES_H
#define TYPES_H


typedef char* avrsh_str_t;
typedef int avrsh_num_t;
typedef struct _op_t{
	char str[3];
	avrsh_str_t (*fun_n)(avrsh_num_t a, avrsh_num_t b);
	avrsh_str_t (*fun_s)(avrsh_str_t a,avrsh_str_t b);
} avrsh_operator_t;

#endif
