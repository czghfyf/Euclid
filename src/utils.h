#ifndef _EUCLID_OAE__UTILS_H_
#define _EUCLID_OAE__UTILS_H_ 1

typedef unsigned long global_id;

global_id *gen_global_id(global_id * gid_p);

void print_byte_binary(char *c);

ssize_t read_socket_data(int cli_socket_fd, void **buf, size_t * buf_len);

int socket_connect_to(int *socket_local_p, char *remote_host, int remote_port);

void *malloc0(size_t size);

#endif
