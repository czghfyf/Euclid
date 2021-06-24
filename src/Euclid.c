#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

#include "comm-proc.h"
#include "cfg.h"
#include "utils.h"
#include "conn.h"
#include "model.h"

static void *cli_thread_startup(void *addr);

static void join_cluster(eCommand * ec);

int main(int argc, char *argv[])
{
	init_cfg(argc, argv);

	init_comm_proc();
	conn_init();

	int server_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct sockaddr_in server_sockaddr;
	memset(&server_sockaddr, 0, sizeof(server_sockaddr));
	server_sockaddr.sin_family = AF_INET;
	server_sockaddr.sin_port = htons(get_cfg()->port);
	server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind
	    (server_sockfd, (struct sockaddr *)&server_sockaddr,
	     sizeof(server_sockaddr)) != 0) {
		printf("error bind %d\n", get_cfg()->port);
		exit(1);
	}

	if (listen(server_sockfd, 20) != 0) {
		printf("error listen\n");
		exit(1);
	}

	while (1) {
		struct sockaddr_in client_addr;

		// TODO what is socklen_t ?
		socklen_t len = sizeof(client_addr);

		int cli_conn =
		    accept(server_sockfd, (struct sockaddr *)&client_addr,
			   &len);

		if (cli_conn < 0) {
			printf("error accept failed.\n");
			continue;
		}

		printf("client[%d] connection succeeded.\n", cli_conn);

		pthread_t thread_id;
		pthread_create(&thread_id, NULL, cli_thread_startup, &cli_conn);
		pthread_detach(thread_id);
	}

	close(server_sockfd);
	return 0;
}

static void *cli_thread_startup(void *addr)
{
	int cli_conn = *((int *)addr);

	void *buf;
	size_t buf_len;

	ssize_t ss = read_socket_data(cli_conn, &buf, &buf_len);
	// printf("firstCommand.read_socket_data.return.ssize_t = %zd\n", ss);
	eCommand *firstCommand = convert_to_command(buf);
	// printf("check first command. command type is %d\n", firstCommand -> command_type);
	// printf("check first command. command length is %d\n", firstCommand -> command_length);
	printf("<<< recv <<< check first command. command type %d\n",
	       firstCommand->command_type);

	if (firstCommand->command_type == CT_INTENT) {
		unsigned short visitor_type =
		    *((unsigned short *)(firstCommand->command));
		freeCommand(firstCommand);

		// printf("command_agree -> command_type is %d\n", command_agree -> command_type);
		// printf("command_agree -> command_length is %d\n", command_agree -> command_length);

		send(cli_conn, command_agree->mem_addr,
		     command_agree->data_pkg_capacity, 0);
		printf(">>> send >>> agree.\n");

		if (visitor_type == 0) {
			while (1) {
				ss = read_socket_data(cli_conn, &buf, &buf_len);
				if (ss < 1)
					break;

				eCommand *ec = convert_to_command(buf);
				printf
				    ("<<< recv <<< ec -> command_type is %d\n",
				     ec->command_type);
				// printf("ec -> command_type is %d\n", ec -> command_type);
				// printf("ec -> command_length is %d\n", ec -> command_length);

				if (ec->command_type == CT_GO_TO_JOIN_CLUSTER) {
					join_cluster(ec);
					send(cli_conn, FIXC_done->mem_addr,
					     FIXC_done->data_pkg_capacity, 0);
					printf(">>> send >>> done.\n");
				} else if (ec->command_type == FIXC_DISCONNECT) {
					freeCommand(ec);
					send(cli_conn, command_agree->mem_addr,
					     command_agree->data_pkg_capacity,
					     0);
					printf(">>> send >>> agree.\n");
					break;
				} else if (ec->command_type == CREATE_DIMENSION) {
					printf("<<< CREATE_DIMENSION - %s\n", ec->command);
					printf("ec->command_length ====================================== %d\n", ec->command_length);

					Dimension * dim = create_dimension(ec->command);

					freeCommand(ec);

					send(cli_conn, FIXC_done->mem_addr, FIXC_done->data_pkg_capacity, 0);
				}

			}

		} else if (visitor_type == 1) {
			printf("visitor is a child node.\n");
		} else {
			printf("Unexpected error.\n");
		}

	}

	close(cli_conn);
}

static void join_cluster(eCommand * ec)
{
//  printf ("Fuction: join_cluster(...) ...\n");
	printf("join to cluster, parent node: %s:%d\n", ec->command,
	       *((int *)(ec->command + 16)));

	char *p_node_host = ec->command;
	int p_node_port = *((int *)(ec->command + 16));
	printf(">>>>>>>>>>>>>>>>> %s:%d\n", p_node_host, p_node_port);

	// int socket_chi = 0;
	// socket_connect_to (&socket_chi, p_node_host, p_node_port);
	SocketConn *scp = socket_conn(p_node_host, p_node_port);
	if (scp == NULL) {
		printf("error: scp == NULL\n");
		return;
	}

	send(scp->socket_fd, fixc_intent_cnode->mem_addr,
	     fixc_intent_cnode->data_pkg_capacity, 0);

	freeCommand(ec);
}
