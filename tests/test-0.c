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
	fn000(1000000, 666);

	printf("IPPROTO_TCP --- %d    %ld\n", IPPROTO_TCP, IPPROTO_TCP);

	printf("sizeof(int) = %d\n", sizeof(int));
	printf("sizeof(unsigned int) = %d\n", sizeof(unsigned int));
	printf("sizeof(long int) = %d\n", sizeof(long int));
	printf("sizeof(long) = %d\n", sizeof(long));
	printf("sizeof(unsigned long) = %d\n", sizeof(unsigned long));
}

fn000(a, b)
int a;
int b;
{
	printf("%d\n", a + b);
}
