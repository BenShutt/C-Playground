#include <stdio.h>

#include "request.h"
#include "endpoints.h"

#define NL "\r\n"

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
        int status_code = rc >= 0 ? OK : BAD_REQUEST;
        http_reply_status(c, status_code, rc);
    }
    else if(mg_http_match_uri(hm, ENDPOINT_UPLOAD))
    {
        // Should not get here as uploads are handled in chunks
        http_reply_status(c, BAD_REQUEST, -1);
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
        return;
    }
    
    bool is_message = (ev == MG_EV_HTTP_MSG || ev == MG_EV_HTTP_CHUNK);
    if(!is_message) return;

    struct mg_http_message *hm = (struct mg_http_message *)ev_data;
    const char *dir = (const char *)fn_data;
    
    if(ev == MG_EV_HTTP_MSG)
    {
        on_http_message(c, hm, dir);
    }
    else if(ev == MG_EV_HTTP_CHUNK && mg_http_match_uri(hm, ENDPOINT_UPLOAD))
    {
        if(hm->chunk.len > 0)
            handle_upload(hm, hm->chunk, dir);

        mg_http_delete_chunk(c, hm);

        if(hm->chunk.len == 0)
        {
            printf("[UPLOAD] Successful.\n");
            http_reply_status(c, OK, 0);
        }
    }
}