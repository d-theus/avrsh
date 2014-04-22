#include "avrsh.h"

avrsh_function_t *avrsh_ftable_find(char *name){
	avrsh_function_t *f;
	HASH_FIND_STR(ftable, name, f);
	return f;
}
avrsh_variable_t *avrsh_vtable_find(char *name){
	avrsh_variable_t *v;
	HASH_FIND_STR(vtable, name, v);
	return v;
}

void avrsh_ftable_insert(char *name, void (*f)(int,char**)){
	avrsh_function_t *nf;
	HASH_FIND_STR(ftable,name,nf);
	if(nf==NULL){
		nf = (avrsh_function_t*)malloc(sizeof(avrsh_function_t));
		nf->name = strdup(name);
		nf->func = f;
	}
	HASH_ADD_KEYPTR(hh, ftable, nf->name, strlen(nf->name),nf);
}
void avrsh_vtable_insert(char *name, char *value){
	avrsh_variable_t *nv;
	HASH_FIND_STR(vtable,name,nv);
	if(nv==NULL){
		nv = (avrsh_variable_t*)malloc(sizeof(avrsh_variable_t));
		nv->name = strdup(name);
		nv->value = strdup(value);
		HASH_ADD_KEYPTR(hh, vtable, nv->name, strlen(nv->name), nv);
	}else{
		free(nv->value);
		nv->value = strdup(value);
	}
}

void avrsh_ftable_delete(char *name){
	avrsh_function_t *ent;
	HASH_FIND_STR(ftable, name, ent);
	if(ent != NULL){
		HASH_DEL(ftable,ent);
		free(ent->name);
		free(ent);
	}
}
void avrsh_vtable_delete(char *name){
	avrsh_variable_t *ent;
	HASH_FIND_STR(vtable, name, ent);
	if(ent != NULL){
		HASH_DEL(vtable,ent);
		free(ent->name);
		free(ent->value);
		free(ent);
	}
}

void avrsh_ftable_clear(){
	avrsh_function_t *s,*tmp;
	HASH_ITER(hh,ftable,s,tmp){
		HASH_DEL(ftable, s);
		free(s->name);
		free(s);
	}
}
void avrsh_vtable_clear(){
	avrsh_variable_t *s,*tmp;
	HASH_ITER(hh,vtable,s,tmp){
		HASH_DEL(vtable, s);
		free(s->name);
		free(s->value);
		free(s);
	}
}

void _avrsh_function_echo(int argc, char **argv){
#ifndef AVR
	int i;
	for(i = 1; i < argc; i++){
		printf("%s\n", argv[i]);
	}
#endif
}

void avrsh_init(){
	ftable = NULL;
	vtable = NULL;

	avrsh_ftable_insert("echo",_avrsh_function_echo);
}

void avrsh_shutdown(){
	avrsh_ftable_clear();
	avrsh_vtable_clear();
}

void avrsh_error(){
	avrsh_shutdown();
	exit(-1);
}
