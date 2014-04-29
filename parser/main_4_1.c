#include "tab.h"
#include "types.h"
#include "parser.h"
#include "avrsh.h"

void _func1(int c, char **v){
}
void _func2(int c, char **v){
}

main(int argc, char **argv){
	avrsh_init();
	avrsh_ftable_clear();
	avrsh_vtable_clear();
	avrsh_ftable_find("one");
	avrsh_vtable_find("one");
	avrsh_ftable_insert("one", _func1);
	avrsh_ftable_insert("one", _func2);
	avrsh_ftable_insert("one", _func1);
	avrsh_ftable_insert("two", _func2);
	avrsh_ftable_delete("two");
	avrsh_ftable_find("one");
	avrsh_vtable_insert("one","ololo");
	avrsh_vtable_insert("one","ololo");
	avrsh_vtable_insert("one","ololo");
	avrsh_vtable_insert("two","ololo");
	avrsh_vtable_delete("two");
	avrsh_shutdown();
}
