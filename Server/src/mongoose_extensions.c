#include <stdlib.h>
#include <string.h>

#include "mongoose_extensions.h"
#include "check.h"

// Carriage return new line string for HTTP
#define NL "\r\n"

const char *c_str(struct mg_str str)
{
    char *target = malloc(sizeof(char) * str.len + sizeof('\0'));
    check_memory(target);
    strncpy(target, str.ptr, str.len);
    target[str.len] = '\0';
    return target;

error:
    return NULL;
}

void http_reply_status(struct mg_connection *c, int status_code, int status)
{
    mg_http_reply(
        c, 
        status_code, 
        "Content-Type: application/json" NL, 
        "{%m:%d}" NL,
        MG_ESC("status"), 
        status
    );
}