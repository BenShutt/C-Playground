#include <stdlib.h>

#include "arguments.h"
#include "socket.h"

int main(int argc, char *argv[])
{
    int rc = -1;
    Arguments *arguments = Arguments_init(argc, argv);
    if(arguments)
    {
        rc = socket_run(arguments);
        Arguments_deinit(arguments);
    }

    return rc == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}