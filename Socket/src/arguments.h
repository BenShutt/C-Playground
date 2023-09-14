#ifndef __arguments_h__
#define __arguments_h__

#include <stdlib.h>

typedef struct Arguments {
    int port;
    size_t n_char;
} Arguments;

// Using a pointer for the return value makes it easier to distinguish between
// success (returning struct) and failure (returning NULL).
Arguments *Arguments_init(int argc, char *argv[]);
void Arguments_deinit(Arguments *arguments);

#endif