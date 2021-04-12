#include <stdio.h>

int main(argc, argv)

int argc;
char *argv[];
{
	fn000(1000000, 666);
}

fn000(a, b)
int a;
int b;
{
	printf("%d\n", a + b);
}
