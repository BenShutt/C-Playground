#ifndef __socket_h__
#define __socket_h__

#include <stdlib.h>

typedef char*(*MessageHandler)(const char *message);

int socket_listen(int port);
int socket_accept(int socket_fd);
char *socket_recv(int connection_fd, size_t n_char);
int socket_send(int connection_fd, const char *message);
int socket_run(int port, size_t n_char, MessageHandler handler);

#endif