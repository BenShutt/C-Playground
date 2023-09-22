#include <stdio.h>

#include "request.h"
#include "endpoints.h"

#define NL "\r\n"
#define STATUS_CODE(C) ((C) >= 0 ? OK : BAD_REQUEST)

static void on_error(const char *message)
{
    const char *error_message = message != NULL ? message : "Unknown error";
    printf("[MG_ERROR] %s.\n", error_message);
}

static void http_reply_status(struct mg_connection *c, StatusCode status_code, int status)
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

static void on_http_message(struct mg_connection *c, struct mg_http_message *hm, const char *dir)
{
    if(mg_http_match_uri(hm, ENDPOINT_STATUS))
    {
        http_reply_status(c, OK, handle_status());
    }
    else if(mg_http_match_uri(hm, ENDPOINT_EXISTS))
    {
        int rc = handle_exists(hm, dir);
        http_reply_status(c, STATUS_CODE(rc), rc);
    }
    else if(mg_http_match_uri(hm, ENDPOINT_UPLOAD))
    {
        int rc = handle_upload(hm, dir);
        http_reply_status(c, STATUS_CODE(rc), rc);
    }
    else
    {
        http_reply_status(c, NOT_FOUND, -1);
    }
}

void on_http_event(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
    if(ev == MG_EV_ERROR)
    {
        const char *message = (char *)ev_data;
        on_error(message);
    }
    else if(ev == MG_EV_HTTP_MSG)
    {
        struct mg_http_message *hm = (struct mg_http_message *)ev_data;
        const char *dir = (const char *)fn_data;
        on_http_message(c, hm, dir);
    } 
}