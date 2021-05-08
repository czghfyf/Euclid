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

#define MYPORT  8768
#define BUFFER_SIZE 1024

static void *read_continuous (void *addr);

int
main ()
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

  pthread_t read_pid;
  pthread_create (&read_pid, NULL, read_continuous, &sock_cli);


  char sendbuf[BUFFER_SIZE];

  while (fgets (sendbuf, sizeof (sendbuf), stdin) != NULL)
    {
      send (sock_cli, sendbuf, strlen (sendbuf), 0);

      memset (sendbuf, 0, sizeof (sendbuf));
    }

  close (sock_cli);
  return 0;
}

static void *
read_continuous (void *addr)
{
  int sock_cli = *((int *) addr);
  char buffer[1024 * 512];	// 512k
  while (1)
    {
      memset (buffer, 0, sizeof (buffer));
      int len = recv (sock_cli, buffer, sizeof (buffer), 0);
      printf ("from server[%d]:\n%s\n", sock_cli, buffer);
    }
}
