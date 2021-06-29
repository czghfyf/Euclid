#include <stdio.h>
#include <string.h>

// #include "cfg.h"
#include "model.h"
#include "utils.h"

#define DIM_ARR_CAPACITY 128

static int dim_arr_index = 0;
static Dimension *dimensions_arr[DIM_ARR_CAPACITY];

static void put_dim(Dimension *dim);

static void put_dim(Dimension *dim)
{
	if (dim_arr_index >= DIM_ARR_CAPACITY) {
		printf("warn: dimensions_arr already fulled. Do Nothing!\n");
		return;
	}
	dimensions_arr[dim_arr_index++] = dim;
}

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

	put_dim(dim);

	return dim;
}
