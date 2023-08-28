#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>

#include "server.h"
#include "check.h"

Server *Server_init()
{
    Server *server = malloc(sizeof(Server));
    check_memory(server);

    server->socket_fd = -1;
    server->connection_fd = -1;
    return server;

error:
    return NULL;
}

void Server_deinit(Server *server)
{
    if(server)
    {
        int connection_fd = server->connection_fd;
        if(connection_fd != -1) close(connection_fd);

        int socket_fd = server->socket_fd;
        if(socket_fd != -1) close(socket_fd);

        free(server);
    }
}

int socket_listen(int port) // private
{
    // Socket file descriptor that may need to be closed regardless of success
    int socket_fd = -1;

    // Get a socket for accepting connections
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    check(socket_fd >= 0, "Failed to open socket.");

    // Server address information
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address.
    int bind_rc = bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr));
    check(bind_rc == 0, "Failed to bind.");

    // Listen for connections. Specify the backlog as 1.
    int listen_rc = listen(socket_fd, 1);
    check(listen_rc == 0, "Failed to listen.");

    return socket_fd;

error:
    if(socket_fd != -1) close(socket_fd);
    return -1;
}

int Server_listen(Server *server, int port)
{
    check(server != NULL, "Invalid argument.");
    server->socket_fd = socket_listen(port);
    return 0;

error:
    return -1;
}

bool Server_validate(Server *server, bool socket, bool connection) // private
{
    if(server == NULL) return false;
    if(socket && server->socket_fd == -1) return false;
    if(connection && server->connection_fd == -1) return false;
    return true;
}

int Server_accept(Server *server)
{
    // Validate the argument
    check(Server_validate(server, true, false), "Invalid argument.");

    // Close any previous connections
    int connection_fd = server->connection_fd;
    if(connection_fd != -1) close(connection_fd);

    // Prepare client
    struct sockaddr_in client;
    socklen_t namelen = (socklen_t)sizeof(client);

    // Client address information
    connection_fd = accept(server->socket_fd, (struct sockaddr *)&client, &namelen);
    check(connection_fd >= 0, "Failed to accept.");
    server->connection_fd = connection_fd;
    
    return 0;

error:
    return -1;
}

char *Server_recv(Server *server, size_t n_char)
{
    char *buf = NULL;

    // Validate the argument
    check(Server_validate(server, true, true), "Invalid argument.");

    // Buffer to read send messages into
    buf = calloc(n_char, sizeof(char));
    check_memory(buf);

    // Receive the message on the newly connected socket
    ssize_t bytes = recv(server->connection_fd, buf, sizeof(buf), 0);
    check(bytes > 0, "Failed to receive data.");

    // Print the received message 
    printf("Received: '%s'\n", buf);

    return buf;

error:
    if(buf) free(buf);
    return NULL;
}

int Server_send(Server *server, const char *message)
{
    // Validate the argument
    check(Server_validate(server, true, true), "Invalid argument.");
    
    // Send message to the client
    ssize_t count = send(server->connection_fd, message, strlen(message), 0);
    check(count >= 0, "Failed to send data");

    return 0;

error:
    return -1;
}

int run_server(int port)
{
    // Pointers that may need to be freed
    char *buf = NULL;
    Server *server = NULL;
    int rc = -1;
    
    // Initialize server
    server = Server_init();
    check(server != NULL, "Server failed to initialize.");
    
    // Listen on port
    rc = Server_listen(server, port);
    check(rc == 0, "Server failed to listen on port %d.", port);

    while(true)
    {
        rc = Server_accept(server);
        check(rc == 0, "Server failed to accept.");

        buf = Server_recv(server, 1024);
        check(buf != NULL, "Server failed to receive.");
        free(buf);

        rc = Server_send(server, "Success");
        check(rc == 0, "Server failed to send");
    }

    return EXIT_SUCCESS;

error:
    if(buf) free(buf);
    Server_deinit(server);
    return EXIT_FAILURE;
}