#ifndef __check_h__
#define __check_h__

#include <stdlib.h>
#include <stdio.h>
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

#define check_memory(C) check((C) != NULL, "Memory error.")

#define assert(C, ...) if(!(C)) {\
    log_error(M, ##__VA_ARGS__);\
    exit(EXIT_FAILURE);}

#endif