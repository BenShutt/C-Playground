#include "socket.h"
#include "file_server.h"

#define PORT 666
#define N_CHARACTERS 1000

int main()
{
    return socket_run(PORT, N_CHARACTERS, file_server_handle);
}