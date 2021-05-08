#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
static void *read_continuous (void *addr);
static void *write_continuous (void *addr);

int
main (int argc, char *argv[])
{
  int server_sockfd = socket (AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in server_sockaddr;
  memset (&server_sockaddr, 0, sizeof (server_sockaddr));
  server_sockaddr.sin_family = AF_INET;
  server_sockaddr.sin_port = htons (8768);
  server_sockaddr.sin_addr.s_addr = htonl (INADDR_ANY);

  struct sockaddr_in client_addr;

  socklen_t len = sizeof (client_addr);

  bind (server_sockfd, (struct sockaddr *) &server_sockaddr,
	sizeof (server_sockaddr));

  listen (server_sockfd, 20);

  int cli_conn =
    accept (server_sockfd, (struct sockaddr *) &client_addr, &len);

  printf ("client connect is %d\n", cli_conn);

  pthread_t read_pid;
  pthread_create (&read_pid, NULL, read_continuous, &cli_conn);

  pthread_t write_pid;
  pthread_create (&write_pid, NULL, write_continuous, &cli_conn);

  while (1)
    sleep (10);

  close (server_sockfd);
  return 0;
}


static void *
read_continuous (void *addr)
{
  int cli_conn = *((int *) addr);
  char buffer[1024 * 512];	// 512k
  while (1)
    {
      memset (buffer, 0, sizeof (buffer));
      int len = recv (cli_conn, buffer, sizeof (buffer), 0);
      printf ("from client[%d]:\n%s\n", cli_conn, buffer);
    }
}


static void *
write_continuous (void *addr)
{
  int cli_conn = *((int *) addr);
  char buffer[1024 * 512];	// 512k

  unsigned int i;
  for (i = 0; i < (1 << 31); i++)
    {
      sleep (2);
      memset (buffer, 0, sizeof (buffer));

      sprintf (buffer, "%d", i);
      send (cli_conn, buffer, strlen (buffer), 0);

    }
}
