#include "tab.h"
#include "types.h"
#include "parser.h"
#include "avrsh.h"

main(int argc, char **argv){
	if(argc < 2)
		printf("Nothing to do\n");
	else
		avrsh_init();
		parse(argv[1]);
		avrsh_shutdown();
		printf("Success\n");
	return 0;
}
