#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	// pointer array
	int * pa[8];
	printf("pointer array --- %d\n", sizeof(pa));

	// array pointer
	int (* ap)[8];
	printf("array pointer --- %d\n", sizeof(ap));
}
