#include "arguments.h"
#include "check.h"

Arguments *Arguments_init(int argc, char *argv[])
{
    check(argc == 3, "Usage: port n_char.");

    int port = atoi(argv[1]);
    check(port > 0, "Invalid port argument.");

    size_t n_char = (size_t)atoi(argv[2]);
    check(n_char > 0, "Invalid n_char argument.");

    Arguments *arguments = malloc(sizeof(Arguments));
    check_memory(arguments);

    arguments->port = port;
    arguments->n_char = n_char;

    return arguments;

error:
    return NULL;
}

void Arguments_deinit(Arguments *arguments)
{
    if(arguments)
        free(arguments);
}