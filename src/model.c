#include <stdio.h>
#include <string.h>

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

	gen_global_id(&(dim->gid));
	printf("********************* %lld\n", dim->gid);

	char dim_file[256];
	memset(dim_file, 0, 256);
	getcwd(dim_file, 220);
	strcat(dim_file, "/meta/dimensions");
	printf("dimensions file absolute path: %s\n", dim_file);

	FILE *fp = fopen(dim_file, "a+");
	fwrite(dim, sizeof(Dimension), 1, fp);
	fclose(fp);

	return dim;
}
