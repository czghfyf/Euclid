#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>

#define MYPORT  8760
#define BUFFER_SIZE 1024

int
main (int argc,char *argv[])
{
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
      exit (1);
    }

  char sendbuf[BUFFER_SIZE];
  char recvbuf[BUFFER_SIZE];
  while (fgets (sendbuf, sizeof (sendbuf), stdin) != NULL)
    {
      send (sock_cli, sendbuf, strlen (sendbuf), 0);

      if (strcmp (sendbuf, "exit\n") == 0)
	break;

      recv (sock_cli, recvbuf, sizeof (recvbuf), 0);

      printf ("from server: %s\n", recvbuf);

      memset (sendbuf, 0, sizeof (sendbuf));
      memset (recvbuf, 0, sizeof (recvbuf));
    }

  close (sock_cli);
  return 0;
}
