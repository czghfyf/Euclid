#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

#define MYPORT  8766
#define BUFFER_SIZE 1024

int
main (int argc, char *argv[])
{
  if (argc < 2)
    {
      printf ("Please specify a command file.\n");
      return 1;
    }

  FILE *fp = fopen (argv[1], "r");
  if (fp == 0)
    {
      printf ("Failed to read file[%s].\n", argv[1]);
      return 1;
    }

  char buff[1024];

  char statement[1024 * 256];	// 256k

  while (1)
    {

      memset (buff, 0, sizeof (buff));
      if (fgets (buff, sizeof (buff), fp) == 0)
	{
	  break;
	}

      strcat (statement, buff);
    }
  fclose (fp);

  int sock_cli = socket (AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in servaddr;
  memset (&servaddr, 0, sizeof (servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons (MYPORT);
  servaddr.sin_addr.s_addr = inet_addr ("127.0.0.1");

  if (connect (sock_cli, (struct sockaddr *) &servaddr, sizeof (servaddr)) <
      0)
    {
      perror ("connect");
      return 1;
    }

  send (sock_cli, statement, strlen (statement) - 1, 0);

  close (sock_cli);

  return 0;

}
