#ifndef __request_h__
#define __request_h__

#include <mongoose.h>

#define ENDPOINT_STATUS "/api/status"
#define ENDPOINT_EXISTS "/api/exists"
#define ENDPOINT_UPLOAD "/api/upload"

#define NL "\r\n"
#define HEADER_FILE_NAME "X-File-Name"

typedef enum StatusCode 
{
    OK = 200,
    BAD_REQUEST = 400,
    NOT_FOUND = 404
} StatusCode;

void on_http_message(struct mg_connection *c, int ev, void *ev_data, void *fn_data);

#endif