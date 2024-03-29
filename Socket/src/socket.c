#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "socket.h"
#include "check.h"

// Newline character(s)
#define NL "\r\n"

// HTTP response to send to the client from the server
const char *make_http_response() // Private
{
    return "HTTP/1.1 200 OK" NL
        "Connection: Close" NL
        "Content-Type: text/plain" NL NL
        "Received" NL;
}

int fd_close(int fd) // Private
{
    if(fd != -1) 
    {
        int rc = close(fd);
        check(rc == 0, "Failed to close file descriptor.");
    }
    return 0;

error:
    return -1;
}

int socket_listen(int port)
{
    // Socket file descriptor that may need to be closed regardless of success
    int socket_fd = -1;

    // Get a socket file descriptor for accepting connections
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    check(socket_fd >= 0, "Failed to open socket.");

    // Server address information
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address.
    int bind_rc = bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr));
    check(bind_rc == 0, "Failed to bind to socket.");

    // Listen for connections. Specify the backlog as 1.
    int listen_rc = listen(socket_fd, 1);
    check(listen_rc == 0, "Failed to listen on socket.");
    return socket_fd;

error:
    fd_close(socket_fd);
    return -1;
}

int socket_accept(int socket_fd)
{
    // Validate the argument
    check(socket_fd != -1, "Invalid argument.");

    // Prepare client
    struct sockaddr_in client;
    socklen_t namelen = (socklen_t)sizeof(client);

    // Client address information
    int connection_fd = accept(socket_fd, (struct sockaddr *)&client, &namelen);
    check(connection_fd >= 0, "Failed to accept.");
    return connection_fd;

error:
    return -1;
}

char *socket_recv(int connection_fd, size_t n_char)
{
    // Buffer to fill with data received
    char *buf = NULL;

    // Validate the argument
    check(connection_fd != -1, "Invalid argument.");

    // Buffer to read send messages into
    buf = calloc(n_char, sizeof(char));
    check_memory(buf);

    // Receive the message on the newly connected socket
    size_t buf_size = (n_char - 1) * sizeof(char);
    ssize_t bytes_read = recv(connection_fd, buf, buf_size, 0);
    check(bytes_read > 0, "Failed to receive data.");
    return buf;

error:
    if(buf) free(buf);
    return NULL;
}

int socket_send(int connection_fd, const char *message)
{
    // Validate the argument
    check(connection_fd != -1, "Invalid argument.");

    // Send message to client
    ssize_t count = send(connection_fd, message, strlen(message), 0);
    check(count >= 0, "Failed to send data.");
    return 0;

error:
    return -1;
}

void print_message(char *message) // Private
{
    printf("========== Start ==========\n");
    printf("%s\n", message);
    printf("========== End ==========\n");
}

void socket_close(int socket_fd, int connection_fd, char *buf) // Private
{
    if(buf) free(buf);
    fd_close(connection_fd);
    fd_close(socket_fd);
}

int socket_run(Arguments *arguments)
{
    int socket_fd = -1;
    int connection_fd = -1;
    char *buf = NULL;

    check(arguments != NULL, "Invalid argument.");

    socket_fd = socket_listen(arguments->port);
    check(socket_fd != -1, "Listen error.");

    while(true)
    {
        fd_close(connection_fd);
        connection_fd = socket_accept(socket_fd);
        check(connection_fd != -1, "Accept error.");

        if(buf) free(buf);
        buf = socket_recv(connection_fd, arguments->n_char);
        check(buf != NULL, "Receive error.");

        print_message(buf);

        int rc = socket_send(connection_fd, make_http_response());
        check(rc == 0, "Send error.");
    }

    socket_close(socket_fd, connection_fd, buf);
    return 0;

error:
    socket_close(socket_fd, connection_fd, buf);
    return -1;
}
