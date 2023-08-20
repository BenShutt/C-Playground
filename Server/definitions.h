#ifndef __definitions_h__
#define __definitions_h__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define errno_to_string() (errno == 0 ? "None" : strerror(errno))

#define log_error(M, ...) fprintf(stderr,\
        "[ERROR] (%s:%d: errno: %s) " M "\n", \
        __FILE__, __LINE__, errno_to_string(), ##__VA_ARGS__)

#define check(C, M, ...) if(!(C)) {\
    log_error(M, ##__VA_ARGS__);\
    errno=0;\
    goto error;}

#endif