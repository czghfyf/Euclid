#include <stdio.h>
#include <string.h>

#include "cfg.h"

static struct config cfg = { 8760 };

static int set_parameters(char *param_name, char *param_val);

struct config *get_cfg()
{
	return &cfg;
}

int init_cfg(int argc, char *argv[])
{
	int i;
	for (i=1;i<argc;i++) {
		char *param_val = strchr(argv[i],'=');

		*param_val = 0;

		set_parameters(argv[i], param_val+1);
	}
}

static int set_parameters(char *param_name, char *param_val)
{
	if (        strcmp(   param_name,"--port"     )    ==0  ) {
		cfg.port =        atoi (param_val);
	}
}
