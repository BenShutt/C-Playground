#ifndef __mongoose_extensions_h__
#define __mongoose_extensions_h__

#include <mongoose.h>

const char *c_str(struct mg_str str);
void http_reply_status(struct mg_connection *c, int status_code, int status);

#endif