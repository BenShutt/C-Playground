#include "arguments.h"
#include "check.h"

Arguments *Arguments_init(int argc, char *argv[])
{
    char *dir = NULL;
    check(argc == 4, "Usage: {port} {n_char} {dir}.");

    int port = atoi(argv[1]);
    check(port > 0, "Invalid port argument.");

    size_t n_char = (size_t)atoi(argv[2]);
    check(n_char > 0, "Invalid n_char argument.");

    dir = strdup(argv[3]);
    check(dir != NULL, "Invalid dir argument.");    

    Arguments *arguments = malloc(sizeof(Arguments));
    check_memory(arguments);

    arguments->port = port;
    arguments->n_char = n_char;
    arguments->dir = dir;

    return arguments;

error:
    if(dir) free(dir);
    return NULL;
}

void Arguments_deinit(Arguments *arguments)
{
    if(arguments)
    {
        if(arguments->dir)
            free(arguments->dir);
        
        free(arguments);
    }
}