#ifdef AVR
#include <stdlib.h>
#else
char *itoa(int i, char *buf, int dummy){
	sprintf(buf,"%d",i);
	return buf;
}
#endif
char * _op_plus(avrsh_num_t a, avrsh_num_t b){
	char *r = (char*)malloc(32); 
	itoa(a+b,r,10);
	return r;
}

char * _op_minus(avrsh_num_t a, avrsh_num_t b){
	char *r = (char*)malloc(32); 
	itoa(a-b,r,10);
	return r;
}

char * _op_times(avrsh_num_t a, avrsh_num_t b){
	char *r = (char*)malloc(32); 
	itoa(a*b,r,10);
	return r;
}

char * _op_div(avrsh_num_t a, avrsh_num_t b){
	char *r = (char*)malloc(32); 
	itoa(a/b,r,10);
	return r;
}

char * _op_mod(avrsh_num_t a, avrsh_num_t b){
	char *r = (char*)malloc(32); 
	itoa(a%b,r,10);
	return r;
}

char * _op_eq_n(avrsh_num_t a, avrsh_num_t b){
	char *r = (char*)malloc(2);
	r[1] = '\0';
	r[0] = (a == b ? 't' : 'f');
	return r;
}

char * _op_gt_n(avrsh_num_t a, avrsh_num_t b){
	char *r = (char*)malloc(2); 
	r[1] = '\0';
	r[0] = (a > b ? 't' : 'f');
	return r;
}

char * _op_lt_n(avrsh_num_t a, avrsh_num_t b){
	char *r = (char*)malloc(2); 
	r[1] = '\0';
	r[0] = (a < b ? 't' : 'f');
	return r;
}

char * _op_geq_n(avrsh_num_t a, avrsh_num_t b){
	char *r = (char*)malloc(2); 
	r[1] = '\0';
	r[0] = (a >= b ? 't' : 'f');
	return r;
}

char * _op_leq_n(avrsh_num_t a, avrsh_num_t b){
	char *r = (char*)malloc(2); 
	r[1] = '\0';
	r[0] = (a <= b ? 't' : 'f');
	return r;
}

char * _op_neq_n(avrsh_num_t a, avrsh_num_t b){
	char *r = (char*)malloc(2); 
	r[1] = '\0';
	r[0] = (a != b ? 't' : 'f');
	return r;
}


char * _op_eq_s(avrsh_str_t a, avrsh_str_t b){
	char *r = (char*)malloc(2);
	r[1] = '\0';
	r[0] = (strcmp(a,b) == 0 ? 't' : 'f');
	return r;
}
char * _op_gt_s(avrsh_str_t a, avrsh_str_t b){
	char *r = (char*)malloc(2);
	r[1] = '\0';
	r[0] = (strcmp(a,b) > 0 ? 't' : 'f');
	return r;
}
char * _op_lt_s(avrsh_str_t a, avrsh_str_t b){
	char *r = (char*)malloc(2);
	r[1] = '\0';
	r[0] = (strcmp(a,b) < 0 ? 't' : 'f');
	return r;
}
char * _op_geq_s(avrsh_str_t a, avrsh_str_t b){
	char *r = (char*)malloc(2);
	r[1] = '\0';
	r[0] = (strcmp(a,b) >= 0 ? 't' : 'f');
	return r;
}
char * _op_leq_s(avrsh_str_t a, avrsh_str_t b){
	char *r = (char*)malloc(2);
	r[1] = '\0';
	r[0] = (strcmp(a,b) <= 0 ? 't' : 'f');
	return r;
}
char * _op_neq_s(avrsh_str_t a, avrsh_str_t b){
	char *r = (char*)malloc(2);
	r[1] = '\0';
	r[0] = (strcmp(a,b) != 0 ? 't' : 'f');
	return r;
}
