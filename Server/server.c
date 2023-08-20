#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "definitions.h"

// Port used for testing
#define PORT 666

// Ref: https://www.ibm.com/docs/en/zos/2.3.0?topic=programs-c-socket-tcp-server

int main()
{
    int socket_fd = -1;
    int connection_fd = -1;

    // Get a socket for accepting connections
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    check(socket_fd >= 0, "Failed to open socket");

    // Server address information
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address.
    int bind_rc = bind(socket_fd, (struct sockaddr *)&server, sizeof(server));
    check(bind_rc == 0, "Failed to bind to socket");

    // Listen for connections. Specify the backlog as 1.
    int listen_rc = listen(socket_fd, 1);
    check(listen_rc == 0, "Failed to listen on socket");

    // Client address information
    struct sockaddr_in client;

    // Accept a connection
    socklen_t namelen = (socklen_t)sizeof(client);
    connection_fd = accept(socket_fd, (struct sockaddr *)&client, &namelen);
    check(connection_fd >= 0, "Failed to accept on socket");

    // Receive the message on the newly connected socket
    char buf[1024];
    ssize_t bytes = recv(connection_fd, buf, sizeof(buf), 0);
    check(bytes >= 0, "Failed to receive data"); // TODO: Handle 0? Just check not -1?

    // Send the message back to the client
    ssize_t count = send(connection_fd, buf, sizeof(buf), 0);
    check(count >= 0, "Failed to send data");

    close(connection_fd);
    close(socket_fd);
    return EXIT_SUCCESS;

error:
    if(connection_fd) close(connection_fd);
    if(socket_fd) close(socket_fd);
    return EXIT_FAILURE;
}