#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	int i = 0;
	for (; i<argc; i++) {
		printf("%d\t%s\n", i, argv[i]);
	}
}
