#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "utils.h"

// static void rewrite_gid_file(char * gid_file, global_id gid);
static void rewrite_gid_file(global_id gid);

// current value
static global_id gid_curval = 0;
// buffer range
static global_id gid_bufran = 1000;
// threshold
static global_id gid_thresh = 0;

void * malloc0(size_t size)
{
	if (size < 1)
		return NULL;

	void * addr = malloc(size);
	memset(addr, 0, size);

	return addr;
}

// static void rewrite_gid_file(char * gid_file, global_id gid)
static void rewrite_gid_file(global_id gid)
{
	char gid_file[256];
	memset(gid_file, 0, 256);
	if (getcwd(gid_file, 220) == NULL) {
		printf("error at fn:rewrite_gid_file(). Program exit.\n");
		exit(1);
	}

	strcat(gid_file, "/meta/global_id");

	FILE * fp = fopen(gid_file, "w+");
	fwrite(&gid, sizeof(gid), 1, fp);
	fclose(fp);
}

global_id *gen_global_id(global_id * gid_p)
{
	if (gid_curval < gid_thresh) {
		*gid_p = gid_curval++;
		if (gid_curval == gid_thresh)
			rewrite_gid_file(gid_thresh = gid_thresh + gid_bufran);
		return gid_p;
	}

	char gid_file[256];
	memset(gid_file, 0, 256);
	if (getcwd(gid_file, 220) == NULL) {
		printf("error at fn:gen_global_id.\n");
		// exit(1);
		return NULL;
	}

	// int gid_len = sizeof(global_id);
	// if (gid_len == 4)
	// 	strcat(gid_file, "/meta/global_id-4");
	// else
	// 	strcat(gid_file, "/meta/global_id-8");

	strcat(gid_file, "/meta/global_id");
	printf("global_id file absolute path: %s\n", gid_file);

	if (access(gid_file, F_OK) == 0) {
		printf("%s is existed.\n", gid_file);
		FILE * fp = fopen(gid_file, "r");
		fread(&gid_curval, sizeof(gid_curval), 1, fp);
	} else {
		printf("No file %s.\n", gid_file);
		gid_curval = 1;
	}

	rewrite_gid_file(gid_thresh = gid_curval + gid_bufran);
	return gen_global_id(gid_p);
}

void
print_byte_binary (char *c)
{
  int offset = 7;
  while (offset >= 0)
    {
      printf ("%d", ((1 << offset--) & *c) ? 1 : 0);
    }
}

ssize_t
read_socket_data (int cli_socket_fd, void **buf, size_t * buf_len)
{
  int pkg_capacity;
  int bs_count;			// count of bytes read at a time
  int buf_cursor = 0;		// It also indicates the total number of bytes that have been read
  int remaining_retry = 10;	// Retry attempts remaining

  do
    {
      bs_count =
	read (cli_socket_fd, ((void *) &pkg_capacity) + buf_cursor,
	      sizeof (pkg_capacity) - buf_cursor);

      if (bs_count < 0)
	return -1;

      if (bs_count == 0 && remaining_retry-- == 0)
	return -1;

      buf_cursor += bs_count;
    }
  while (buf_cursor < sizeof (pkg_capacity));

  if (pkg_capacity <= sizeof (pkg_capacity))
    return -1;

  char *m_buf = malloc (pkg_capacity);	// memory buffer must be freed elsewhere!

  memcpy (m_buf, &pkg_capacity, sizeof (pkg_capacity));

  while (buf_cursor < pkg_capacity)
    {
      bs_count =
	read (cli_socket_fd, m_buf + buf_cursor, pkg_capacity - buf_cursor);
      buf_cursor += bs_count;
    }

//   printf ("data package capacity = %d\n", pkg_capacity);
//   printf ("data package content length = %d\n",
// 	  pkg_capacity - sizeof (pkg_capacity));

  *buf = m_buf;
  return *buf_len = pkg_capacity;
}

int socket_connect_to(int * socket_local_p, char * remote_host, int remote_port)
{
  int socket_local = socket (AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in servaddr;
  memset (&servaddr, 0, sizeof (servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons (remote_port);
  servaddr.sin_addr.s_addr = inet_addr (remote_host);

  if (connect (socket_local, (struct sockaddr *) &servaddr, sizeof (servaddr)) == 0) {
		*socket_local_p = socket_local;
		return 0;
	} else {
       printf("error. connect %s:%d\n", remote_host, remote_port);
		return -1;
	}
}
