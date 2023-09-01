#ifndef __arguments_h__
#define __arguments_h__

#include <stdlib.h>

typedef struct Arguments {
    int port;
    size_t n_char;
    char *dir;
} Arguments;

Arguments *Arguments_init(int argc, char *argv[]);
void Arguments_deinit(Arguments *arguments);

#endif