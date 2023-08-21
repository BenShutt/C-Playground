#ifndef __definitions_h__
#define __definitions_h__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define strerrno() (errno == 0 ? "None" : strerror(errno))

#define log_error(M, ...) fprintf(stderr,\
    "[ERROR] (%s:%d: errno: %s) " M "\n",\
    __FILE__, __LINE__, strerrno(), ##__VA_ARGS__)

#define check(C, M, ...) if(!(C)) {\
    log_error(M, ##__VA_ARGS__);\
    errno=0;\
    goto error;}

#endif