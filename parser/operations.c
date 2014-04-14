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

char * _op_eq(avrsh_str_t a, avrsh_str_t b){
	char *r = (char*)malloc(32); 
	r[1] = '\0';
	r[0] = (strcmp(a,b) == 0 ? 't' : 'f');
	return r;
}

char * _op_gt(avrsh_num_t a, avrsh_num_t b){
	char *r = (char*)malloc(32); 
	char as[32], bs[32];
	r[1] = '\0';
	r[0] = (strcmp(itoa(a,as,10),itoa(b,bs,10)) > 0 ? 't' : 'f');
	return r;
}

char * _op_lt(avrsh_num_t a, avrsh_num_t b){
	char *r = (char*)malloc(32); 
	char as[32], bs[32];
	r[1] = '\0';
	r[0] = (strcmp(itoa(a,as,10),itoa(b,bs,10)) < 0 ? 't' : 'f');
	return r;
}
