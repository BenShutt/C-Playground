#ifndef __request_parts_h__
#define __request_parts_h__

#include <stdlib.h>

/**
 * A request is composed of:
 * 1) A JSON describing the file in the request
 * 2) The file data
 * 
 * The parts are separated by a new line character.
 * The JSON should not contain a new line character.
 */
typedef struct RequestParts {
    char *json;
    char *data;
} RequestParts;

RequestParts *RequestParts_init(const char *message);
void RequestParts_deinit(RequestParts *request_parts);
int RequestParts_trim_data(RequestParts *request_parts, size_t size);

#endif