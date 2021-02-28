#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "vce_common.h"

int open_svr_socket(int port)
{
	// create
	int listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

	// bind
	bind(listen_socket, (struct sockaddr *)&addr, sizeof(addr));

	// listen
	listen(listen_socket, 10);

	return listen_socket;
} // fn open_svr_socket end

int create_tcp_link(char *target_ip, int target_port)
{
	int socket_id = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_id < 1) {
		logW("socket_id = %d", socket_id);
		return -1;
	}

	struct sockaddr_in sock_ai;
    sock_ai.sin_family = AF_INET;
    sock_ai.sin_port = htons(target_port);
    sock_ai.sin_addr.s_addr = htonl(INADDR_ANY);
    inet_aton(target_ip, &(sock_ai.sin_addr));

    if (connect(socket_id, (struct sockaddr *) &sock_ai, sizeof(sock_ai)) != 0) {
		logW("fn:create_tcp_link > connect failed");
        return -1;
    }

	return socket_id;
} // fn create_tcp_link end

int unsigned_int_list_comp(unsigned int *a, unsigned int *b, int size)
{
	int i;
	for (i = 0; i < size; i++) {
		if (a[i] < b[i])
			return -1;
		if (a[i] > b[i])
			return 1;
	}
	return 0;
}

void unsigned_int_list_exchange(unsigned int *a, unsigned int *b, int size)
{
	unsigned int exchg_space[size * sizeof(unsigned int)];
	memcpy(exchg_space, a, size * sizeof(unsigned int));
	memcpy(a, b, size * sizeof(unsigned int));
	memcpy(b, exchg_space, size * sizeof(unsigned int));
}

int ug_int_cmp(void *a, void *b, unsigned int cmp_len)
{
	unsigned int *a_ = (unsigned int *) a, *b_ = (unsigned int *) b;
	while (cmp_len-- > 0) {
		if (*a_++ != *b_++) return *(a_ - 1) > *(b_ - 1) ? 1 : -1;
	}
	return 0;
}

ssize_t read_data_pkg(int client_socket, void *buf, size_t buf_size)
{
	ssize_t pkg_len, r_len, buf_mk = 0;
	char tolerate_read_0 = 30;
	
	do {
		r_len = read(client_socket, buf + buf_mk, buf_size - buf_mk);
		if (r_len < 0) {
			logD("// temp > exception in client socket. r_len < 0.\n");
			return -1;
		}
		if (r_len == 0 && (--tolerate_read_0 == 0)) {
			logD("// temp > Returned too many times 0.\n");
			return 0;
		}
		buf_mk += r_len;
	} while (buf_mk < 4);

	pkg_len = ((unsigned int *) buf)[0];

	if (pkg_len > buf_size) {
		printf(
			"The buffer[%d] is smaller than the amount of data[%d] that will be read and the packet will be discarded.\n",
			buf_size, pkg_len);
		while (buf_mk < pkg_len) {
			r_len = read(client_socket, buf, buf_size);
			buf_mk += r_len;
		}
		return 0;
	}

	while (buf_mk < pkg_len) {
		r_len = read(client_socket, buf + buf_mk, buf_size - buf_mk);
		buf_mk += r_len;
	}

	if (buf_mk != pkg_len || buf_mk > buf_size) {
		logD("// temp > ERROR! buf_mk[%d] is too long. buffer area size is[%d].\n", buf_mk, buf_size);
		return -1;
	}

	return pkg_len;
} // function read_data_pkg() end

ssize_t read_tcp_pkg(int client_socket, void **buf, size_t *buf_size)
{
	int pkg_len, r_len, buf_mk = 0, tolerate_read_0 = 10;
	
	do {
		r_len = read(client_socket, ((void *) &pkg_len) + buf_mk, sizeof(pkg_len) - buf_mk);
		if (r_len < 0) {
			logE("fn:read_tcp_pkg > exception in client socket. r_len < 0.");
			return -1;
		}
		if (r_len == 0 && (--tolerate_read_0 == 0)) {
			logE("fn:read_tcp_pkg > Returned too many times 0.");
			return 0;
		}
		buf_mk += r_len;
	} while (buf_mk < sizeof(pkg_len));

	if (pkg_len <= sizeof(pkg_len) ) {
		logE("fn:read_tcp_pkg > null tcp package");
		return -2;
	}

	void *mem_addr = malloc(pkg_len); // memory must be freed elsewhere!
	if (mem_addr == NULL) {
		logE("fn:read_tcp_pkg > malloc return NULL");
		return -3;
	}

	memcpy(mem_addr, &pkg_len, sizeof(pkg_len));
	while (buf_mk < pkg_len) {
		r_len = read(client_socket, mem_addr + buf_mk, pkg_len - buf_mk);
		buf_mk += r_len;
	}

	if (buf_mk != pkg_len) {
		logE("fn:read_tcp_pkg > buf_mk[%d] != pkg_len[%d]", buf_mk, pkg_len);
		return -4;
	}

	*buf = mem_addr;
	*buf_size = pkg_len;

	return pkg_len;
} // function read_tcp_pkg() end

