#include <stdio.h>
// #include <arpa/inet.h>
// #include <string.h>
#include <stdlib.h>

#include "conn.h"
#include "utils.h"

int conn_init()
{
	printf("::connection manager init...\n");
	printf("sizeof(SocketPool) = %d\n", sizeof(SocketPool));
	downstream_sockets = malloc(sizeof(SocketPool));
}

int socPoo_put(SocketConn * sc, SocketPool * sp)
{
	if (sc == NULL)
		return -1;

	if (sp == NULL)
		sp = downstream_sockets;

	if (sp -> count == POOL_CAPACITY - 1)
		return -2;

	sp -> scs[sp -> count] = sc;
	(sp -> count)++;

	return 0;
}

SocketConn * socket_conn(char * remote_host, int remote_port)
{
	int socket_;
	if (socket_connect_to(&socket_, remote_host,remote_port) == 0) {
		SocketConn * scp = malloc(sizeof(SocketConn));
		scp->socket_fd = socket_; 
		return scp;
	} else {
		return NULL;
	}
}
