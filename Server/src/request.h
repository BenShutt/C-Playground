#ifndef __request_h__
#define __request_h__

#include <stdlib.h>

#include "request_parts.h"

typedef struct Request {
    char *file_name;
    size_t size;
    char *data; // TODO: uint8_t
} Request;

Request *Request_init(RequestParts *request_parts);
void Request_deinit(Request *request);
void Request_print(Request *request);

#endif