#include <stdlib.h>

#include "arguments.h"
#include "socket.h"
#include "file.h"
#include "file_server.h"

int main(int argc, char *argv[])
{
    int rc = -1;
    Arguments *arguments = Arguments_init(argc, argv);
    if(arguments)
    {
        rc = socket_run(arguments, file_server_handle);
        Arguments_deinit(arguments);
    }

    return rc == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}