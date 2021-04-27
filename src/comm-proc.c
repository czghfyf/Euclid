#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comm-proc.h"

extern int scan_comm_stat(const char *cs);
extern void cleanup_yy_str_buff();
extern int yyparse(void);

void process_command(char *command_stat)
{
	// TODO
	printf("processing:\n%s\n", command_stat);

	scan_comm_stat(command_stat);

	free(command_stat);

	yyparse();
	cleanup_yy_str_buff();

}

