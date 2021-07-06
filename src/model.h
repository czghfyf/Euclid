#ifndef _EUCLID_OAE__MODEL_H_
#define _EUCLID_OAE__MODEL_H_ 1

#define DIM_STCT_NAME_LEN 128

#include "utils.h"

typedef struct dimension_stct {
	global_id gid;
	char name[DIM_STCT_NAME_LEN];
} Dimension;

typedef struct member_stct {
	global_id gid;
	global_id p_gid;
	char name[DIM_STCT_NAME_LEN];
	global_id dim_gid;
} Member;

Dimension *create_dimension(char *name);

void model_init();

#endif
