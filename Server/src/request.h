#ifndef __request_h__
#define __request_h__

#include <mongoose.h>

typedef enum StatusCode 
{
    OK = 200,
    BAD_REQUEST = 400,
    NOT_FOUND = 404
} StatusCode;

void on_http_event(struct mg_connection *c, int ev, void *ev_data, void *fn_data);

#endif