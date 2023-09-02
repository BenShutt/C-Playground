#ifndef __request_parts_h__
#define __request_parts_h__

#include <stdlib.h>

typedef struct RequestParts {
    char *json;
    char *data;
} RequestParts;

RequestParts *RequestParts_init(const char *message);
void RequestParts_deinit(RequestParts *request_parts);
int RequestParts_trim_data(RequestParts *request_parts, size_t size);

#endif