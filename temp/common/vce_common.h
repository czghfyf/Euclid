#ifndef _VCE_COMMON_H_
#define _VCE_COMMON_H_ 1

struct simple_link_node {
	void *p;
	struct simple_link_node *prev;
	struct simple_link_node *next;
};

int open_svr_socket(int port);

int create_tcp_link(char *target_ip, int target_port);

// return a < b ? -1 : (a > b ? 1 : 0)
int unsigned_int_list_comp(unsigned int *a, unsigned int *b, int size);

void unsigned_int_list_exchange(unsigned int *a, unsigned int *b, int size);

int ug_int_cmp(void *a, void *b, unsigned int cmp_len);

ssize_t read_data_pkg(int client_socket, void *buf, size_t buf_size);

ssize_t read_tcp_pkg(int client_socket, void **buf, size_t *buf_size);

#endif
