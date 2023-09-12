#ifndef __socket_h__
#define __socket_h__

#include <stdlib.h>
#include "arguments.h"

int socket_listen(int port);
int socket_accept(int socket_fd);
char *socket_recv(int connection_fd, size_t n_char);
int socket_send(int connection_fd, const char *message);
int socket_run(Arguments *arguments);

#endif