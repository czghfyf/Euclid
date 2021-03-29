#include <stdio.h>

#include "utils.h"

int main(int argc, char *argv[])
{
	char cs[] = {'A', 'X', 'h', 'f', ' ', '\t', '\n', '&'};

	/*
	0100 0001
	0101 1000
	0110 1000
	0110 0110
	0010 0000
	0000 1001 ?
	0000 1010 ?
	0010 0110
	*/

	int i;
	for (i = 0; i < 8; i++) {
	 	print_byte_binary(cs + i);
		printf("\n");
		
	}

	return 0;
}
