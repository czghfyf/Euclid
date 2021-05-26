#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

#include "constants.h"

#define MYPORT  8760
#define BUFFER_SIZE 1024

char *p_host;
int p_port;
char *p_join_node_host;
int p_join_node_port;

void extract_param(char *param);

int
main (int argc, char *argv[])
{
  int i = 1;
  while (i < argc) {
    printf("param[%d] %s\n", i, argv[i]);
    extract_param(argv[i]);
    ++i;
  }

  int sock_cli = socket (AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in servaddr;
  memset (&servaddr, 0, sizeof (servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons (p_port);
  servaddr.sin_addr.s_addr = inet_addr (p_host);

  if (connect (sock_cli, (struct sockaddr *) &servaddr, sizeof (servaddr)) < 0) {
       printf("error. connect %s:%d\n", p_host, p_port);
      return 1;
    }

       printf("already connected %s:%d\n", p_host, p_port);

//  send (sock_cli, statement, strlen (statement) - 1, 0);
       char intent[8];
       memset(intent, 0, 8);
       intent[0] = 8;

       send(sock_cli, intent, 8, 0);

  close (sock_cli);












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


  return 0;

}

void extract_param(char *param)
{
  char *val = strchr(param, '=');
  *val = 0;
  ++val;
  printf("param key[%s] val[%s]\n", param, val);

  if (strcmp(param, P_HOST) == 0) {
    p_host = val;
  }

  if (strcmp(param, P_PORT) == 0) {
    p_port = atoi(val);
  }

  if (strcmp(param, P_JOIN_NODE_HOST) == 0) {
    p_join_node_host = val;
  }

  if (strcmp(param, P_JOIN_NODE_PORT) == 0) {
    p_join_node_port = atoi(val);
  }

}
