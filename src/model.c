#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// #include "cfg.h"
#include "model.h"
#include "utils.h"

#define DIM_ARR_CAPACITY 128

static int dim_arr_index = 0;
static Dimension *dimensions_arr[DIM_ARR_CAPACITY];

static void put_dim(Dimension *dim);

void model_init()
{
	printf("model.h: model_init() be called.\n");

	char dim_file[256];
	memset(dim_file, 0, 256);
	getcwd(dim_file, 220);
	strcat(dim_file, "/meta/dimensions");

	// printf("dimensions file absolute path: %s\n", dim_file);
	FILE *fp = fopen(dim_file, "a+");
	// fwrite(dim, sizeof(Dimension), 1, fp);

	Dimension *dim_p = (Dimension *)malloc0(sizeof(Dimension));
	while (fread(dim_p, sizeof(Dimension), 1, fp) > 0) {
		put_dim(dim_p);
		// size_t  fread(void *buffer, size_t size, size_t count, FILE * stream);
		// char vvvvv[256];
		// size_t r_size = ;
		// printf(")))))))))))))))))))))))))))))))))>>>>>>    %lld\n", r_size);
	}

	free(dim_p);


	fclose(fp);
}

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
