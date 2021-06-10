#ifndef __EUCLID_CONNECTION_H__
#define __EUCLID_CONNECTION_H__ 1

#define POOL_CAPACITY 128

typedef struct socket_conn_stct {
	int socket_fd;
} SocketConn;

typedef struct socket_pool_stct {
	int count;
	SocketConn * scs[POOL_CAPACITY];
} SocketPool;

SocketPool *downstream_sockets;

int conn_init();

int socPoo_put(SocketConn * sc, SocketPool * sp);

SocketConn * socket_conn(char * remote_host, int remote_port);

#endif
