#ifndef __request_h__
#define __request_h__

#include <mongoose.h>

void on_http_message(struct mg_connection *c, int ev, void *ev_data, void *fn_data);

#endif