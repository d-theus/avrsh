#include "tab.h"
#include "types.h"
#include "parser.h"
#include "avrsh.h"

main(int argc, char **argv){
	avrsh_init();
	avrsh_shutdown();
	return 0;
}
