#include <stdio.h>
#include <stdbool.h>

#include "request.h"
#include "endpoints.h"
#include "mongoose_extensions.h"

static void on_error(const char *message)
{
    const char *error_message = message != NULL ? message : "Unknown error";
    printf("[MG_EV_ERROR] %s.\n", error_message);
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
        StatusCode status_code = rc >= 0 ? OK : BAD_REQUEST;
        http_reply_status(c, status_code, rc);
    }
    else if(mg_http_match_uri(hm, ENDPOINT_UPLOAD))
    {
        // Should not get here since uploads are handled as chunks
        http_reply_status(c, BAD_REQUEST, -1);
    }
    else
    {
        http_reply_status(c, NOT_FOUND, -1);
    }
}

static void on_http_chunk_message(struct mg_connection *c, struct mg_http_message *hm, const char *dir)
{
    bool is_uploading = mg_http_match_uri(hm, ENDPOINT_UPLOAD);
    if(!is_uploading) return;

    if(hm->chunk.len > 0)
    {
        handle_upload(hm, hm->chunk, dir, false); // Error masked
    }

    mg_http_delete_chunk(c, hm);

    if(hm->chunk.len == 0)
    {
        int rc = handle_upload(hm, hm->chunk, dir, true);
        StatusCode status_code = rc == 0 ? OK : BAD_REQUEST;
        http_reply_status(c, status_code, rc);
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

    bool can_handle = (ev == MG_EV_HTTP_MSG || ev == MG_EV_HTTP_CHUNK);
    if(!can_handle) return;

    struct mg_http_message *hm = (struct mg_http_message *)ev_data;
    const char *dir = (const char *)fn_data;

    if(ev == MG_EV_HTTP_MSG)
    {
        on_http_message(c, hm, dir);
    }
    else if(ev == MG_EV_HTTP_CHUNK)
    {
        on_http_chunk_message(c, hm, dir);
    }
}