#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef struct a_stct {
	char name[8];
	int i;
	int j;
} AST;

int main(argc, argv)

int argc;
char *argv[];
{
	// char s1[20];
	// printf("%d\n-----------------------------------------\n", strlen(s1));
	// printf("%d\n-----------------------------------------\n", sizeof(AST));

	AST * ast0 = malloc(sizeof(AST));
	printf("16 ? %d\n", sizeof(AST));

	ast0 -> i = 0;
	ast0 -> j = 0;
	printf("%s\n", ast0 -> name);
	printf("%d, %d\n", ast0 -> i,ast0->j);

	char * s1 = "0000xxxx";
	strcpy(ast0 -> name, s1);
	printf("%s\n", ast0 -> name);
	printf("%d, %d\n", ast0 -> i,ast0->j);

	char * s2 = "0000xxxx.....";
	strcpy(ast0 -> name, s2);
	printf("%s\n", ast0 -> name);
	printf("%d, %d\n", ast0 -> i,ast0->j);
	
}
