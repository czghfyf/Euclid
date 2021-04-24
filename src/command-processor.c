#include <stdio.h>
#include <stdlib.h>

#include "command-processor.h"

void process_command(char *command_stat)
{
	// TODO
	printf("processing:\n%s\n", command_stat);

	free(command_stat);
}

