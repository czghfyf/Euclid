#include <stdio.h>

int main(int argc, char *argv[])
{
	unsigned long i = 0;
	while (1) {
		if (i % 100000000 == 0)
			printf("running... %lu\n", i);
		i++;
	}
	return 0;
}
