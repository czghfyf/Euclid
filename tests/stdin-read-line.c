#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main (argc, argv)
     int argc;
     char *argv[];
{

  int size = 8;
  char *buff = (char *) malloc (size);

  while (NULL != fgets (buff, size, stdin))
    {
      printf ("---------------------------- size = %d\n", size);
      printf ("Read line with len: %d\n", strlen (buff));
      printf ("%s", buff);
    }
  free (buff);
}
