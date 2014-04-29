#include "tab.h"
#include "types.h"
#include "parser.h"
#include "avrsh.h"

void func(int argc, char **argv){
	int i;
	for(i = argc-1; i >= 0; i--){
		printf("%s\n",argv[i]);
	}
}

main(int argc, char **argv){
	if(argc < 2)
		printf("Nothing to do\n");
	else
		avrsh_init();
		avrsh_ftable_insert("myfunction", func);
		parser_parse(argv[1]);
		avrsh_shutdown();
		printf("Success\n");
	return 0;
}
