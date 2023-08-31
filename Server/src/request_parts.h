#ifndef __request_parts_h__
#define __request_parts_h__

#include <stdint.h>

typedef struct RequestParts {
    char *json;
    char *data; // TODO: uint8_t
} RequestParts;

RequestParts *RequestParts_init(const char *message);
void RequestParts_deinit(RequestParts *request_parts);

#endif