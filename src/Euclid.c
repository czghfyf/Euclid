#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

#include "comm-proc.h"
#include "cfg.h"
#include "utils.h"

static void *cli_thread_startup (void *addr);

int
main (int argc, char *argv[])
{
  init_cfg (argc, argv);

  int server_sockfd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);

  struct sockaddr_in server_sockaddr;
  memset (&server_sockaddr, 0, sizeof (server_sockaddr));
  server_sockaddr.sin_family = AF_INET;
  server_sockaddr.sin_port = htons (get_cfg ()->port);
  server_sockaddr.sin_addr.s_addr = htonl (INADDR_ANY);

  if (bind (server_sockfd,
	    (struct sockaddr *) &server_sockaddr,
	    sizeof (server_sockaddr)) != 0)
    {
      printf ("error bind 8760\n");
      exit (1);
    }

  if (listen (server_sockfd, 20) != 0)
    {
      printf ("error listen\n");
      exit (1);
    }

  while (1)
    {
      struct sockaddr_in client_addr;

      // TODO what is socklen_t ?
      socklen_t len = sizeof (client_addr);

      int cli_conn =
	accept (server_sockfd, (struct sockaddr *) &client_addr, &len);

      if (cli_conn < 0)
	{
	  printf ("error accept failed.\n");
	  continue;
	}

      printf ("client[%d] connection succeeded.\n", cli_conn);

      pthread_t thread_id;
      pthread_create (&thread_id, NULL, cli_thread_startup, &cli_conn);
      pthread_detach (thread_id);
    }

  close (server_sockfd);
  return 0;
}

static void *
cli_thread_startup (void *addr)
{
  int cli_conn = *((int *) addr);
  // char buffer[1024 * 512];   // 512k

  void *buf;
  size_t buf_len;

  while (1)
    {
      read_socket_data (cli_conn, &buf, &buf_len);

      // TODO Copy the command statement, and hand it over to the command processor for processing.
      // process_command(buf);

      send (cli_conn, "done", strlen ("done"), 0);
    }

  close (cli_conn);
}
