#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

#include "constants.h"
#include "comm-proc.h"
#include "utils.h"

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
	init_comm_proc();



//  int sock_cli = socket (AF_INET, SOCK_STREAM, 0);
//
//  struct sockaddr_in servaddr;
//  memset (&servaddr, 0, sizeof (servaddr));
//  servaddr.sin_family = AF_INET;
//  servaddr.sin_port = htons (p_port);
//  servaddr.sin_addr.s_addr = inet_addr (p_host);
//
//  if (connect (sock_cli, (struct sockaddr *) &servaddr, sizeof (servaddr)) < 0) {
//       printf("error. connect %s:%d\n", p_host, p_port);
//      return 1;
//    }

	int sock_cli = 0;
	if (socket_connect_to(&sock_cli, p_host, p_port) != 0) {
       printf("error. connect %s:%d\n", p_host, p_port);
      return 1;
	}



       printf("already connected %s:%d\n", p_host, p_port);

       // char intent[8];
       // memset(intent, 0, 8);
       // intent[0] = 8;
       // send(sock_cli, intent, 8, 0);
		send(sock_cli, fixc_intent_cli -> mem_addr, fixc_intent_cli -> data_pkg_capacity, 0);
	printf(">>> send >>> intent.\n");


  void *buf;
  size_t buf_len;

       read_socket_data (sock_cli, &buf, &buf_len);
       eCommand *serv_resp = convert_to_command(buf);
	printf("<<< recv <<< command_type %d\n", serv_resp -> command_type);
//       	  printf("serv_resp -> command_type is %d\n", serv_resp -> command_type);
//       	  printf("serv_resp -> command_length is %d\n", serv_resp -> command_length);

	if (serv_resp -> command_type != CT_AGREE) {
  		close (sock_cli);
		printf("the connection request was rejected by server.\n");
		return 1;
	}

	if (p_join_node_host != NULL) {

		char *mem_addr = malloc(26);
		memset(mem_addr, 0, 26);
		*((int *) mem_addr) = 26;
		*((short *) (mem_addr + 4)) = CT_GO_TO_JOIN_CLUSTER;
		strcpy(mem_addr + 6, p_join_node_host);
		*((int *) (mem_addr + 22)) = p_join_node_port;

		eCommand *join_cluster_command = convert_to_command(mem_addr);
		// printf("join_cluster_command -> mem_addr %p\n", join_cluster_command -> mem_addr);
		// printf("join_cluster_command -> data_pkg_capacity %d\n", join_cluster_command -> data_pkg_capacity);
        send(sock_cli, join_cluster_command -> mem_addr, join_cluster_command -> data_pkg_capacity, 0);
		printf(">>> send >>> go to join[%s:%d] a cluster.\n", join_cluster_command->command, *((int *)(join_cluster_command->command + 16))  );


       read_socket_data (sock_cli, &buf, &buf_len);
       serv_resp = convert_to_command(buf);
       	  // printf("serv_resp -> command_type is %d\n", serv_resp -> command_type);
       	  // printf("serv_resp -> command_length is %d\n", serv_resp -> command_length);
		printf("<<< recv <<< command_type %d\n", serv_resp -> command_type);

		goto cli_exit;
	}

	cli_exit:
        send(sock_cli, fixcDisconnect -> mem_addr, fixcDisconnect -> data_pkg_capacity, 0);
		printf(">>> send >>> disconnect.\n");


       read_socket_data (sock_cli, &buf, &buf_len);
       serv_resp = convert_to_command(buf);
       	  // printf("cli try exit. server replay: command_type %d\n", serv_resp -> command_type);
       	  // printf("cli try exit. server replay: command_length %d\n", serv_resp -> command_length);
		printf("<<< recv <<< command_type %d\n", serv_resp -> command_type);

  close (sock_cli);

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
