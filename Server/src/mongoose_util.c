#include <stdlib.h>
#include "mongoose_util.h"

void http_reply_status(struct mg_connection *c, int http_status_code, int status)
{
    mg_http_reply(
        c, 
        http_status_code, 
        "Content-Type: application/json" NL, 
        "{%m:%d}" NL,
        MG_ESC("status"), 
        status
    );
}