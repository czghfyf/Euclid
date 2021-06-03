#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	int i = 100000;
	int x = 9099 % 9090;
	long l = i + x;
	printf("%l\n", l);
}
