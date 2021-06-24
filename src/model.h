#ifndef _EUCLID_OAE__MODEL_H_
#define _EUCLID_OAE__MODEL_H_ 1

#define DIM_STCT_NAME_LEN 128

#include "utils.h"

typedef struct dimension_stct {
	global_id gid;
	char name[DIM_STCT_NAME_LEN];
} Dimension;

Dimension *create_dimension(char *name);

#endif
