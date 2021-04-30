#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"

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
