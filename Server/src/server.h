#ifndef __server_h__
#define __server_h__

#include <stdlib.h>

typedef struct Server 
{
    int socket_fd;
    int connection_fd;
} Server;

Server *Server_init();
void Server_deinit(Server *server);
int Server_listen(Server *server, int port);
int Server_accept(Server *server);
char *Server_recv(Server *server, size_t n_char); // Should free return
int Server_send(Server *server, const char *message);

int run_server(int port);

#endif