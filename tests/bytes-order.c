#include <stdio.h>
 // #include <sys/types.h>
 // #include <sys/socket.h>
 // #include <netinet/in.h>
 #include <arpa/inet.h>
 // #include <unistd.h>
 // #include <string.h>
 #include <stdlib.h>

int main(argc, argv)

int argc;
char *argv[];
{
	// signed int i = 255;
	signed int i = 177213951;
	char *c = (char *) &i;

	// printf("%02x\n", *c);
	// c++;
	// printf("%02x\n", *c);
	// c++;
	// printf("%02x\n", *c);
	// c++;
	// printf("%02x\n", *c);

	printf("%d\n", *c);
	c++;
	printf("%d\n", *c);
	c++;
	printf("%d\n", *c);
	c++;
	printf("%d\n", *c);
	c++;
}

