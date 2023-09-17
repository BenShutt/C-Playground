#ifndef __mongoose_util_h__
#define __mongoose_util_h__

#include <mongoose.h>

#define NL "\r\n"

void http_reply_status(struct mg_connection *c, int http_status_code, int status);

#endif