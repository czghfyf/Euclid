#include <stdio.h>

#include "utils.h"

void print_byte_binary(char *c)
{
	int offset = 7;
	while (offset >= 0) {
		printf("%d", ((1 << offset--) & *c) ? 1 : 0);
	}
}

