#include <stdio.h>
#include <string.h>
// 
// #include "cfg.h"
#include "model.h"
#include "utils.h"

Dimension *create_dimension(char *name)
{
	if (strlen(name) > DIM_STCT_NAME_LEN) {
		return NULL;
	}

	Dimension *dim = (Dimension *) malloc0(sizeof(Dimension));

	int name_len =
	    strlen(name) < DIM_STCT_NAME_LEN ? strlen(name) : DIM_STCT_NAME_LEN;

	// global_id gid;
	gen_global_id(&(dim->gid));
	printf("****************************************************** %lld\n",
	       dim->gid);

	return dim;
}
