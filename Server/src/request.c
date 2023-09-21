#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#include "request.h"
#include "check.h"
#include "file.h"

static int handle_exists(struct mg_http_message *hm, const char *dir)
{
    // Make URL
    char *url = (char *)make_file_url(hm, dir);
    check(url != NULL, "Failed to make URL.");

    // Check if the file exists
    int rc = access(url, F_OK) == 0;
    printf("[EXISTS] %s for '%s'.\n", BOOL_STR(rc), url);

    // Clean up and return success
    free(url);
    return rc;

error:
    if(url) free(url);
    return -1;
}

static int handle_upload(struct mg_http_message *hm, const char *dir)
{
    // Make URL
    char *url = (char *)make_file_url(hm, dir);
    check(url != NULL, "Failed to make URL.");

    // Write HTTP body to file
    int rc = write_file((u_int8_t *)hm->body.ptr, hm->body.len, url);
    check(rc == 0, "Failed to write file.");

    // Print success
    printf("[UPLOAD] %ld bytes successfully written to '%s'.\n", hm->body.len, url);
    
    // Clean up and return success
    free(url);
    return 0;

error:
    if(url) free(url);
    return -1;
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

static void http_reply(struct mg_connection *c, int rc)
{
    int status_code = rc >= 0 ? OK : BAD_REQUEST;
    http_reply_status(c, status_code, rc);
}

void on_http_message(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
    if(ev != MG_EV_HTTP_MSG) return;

    struct mg_http_message *hm = (struct mg_http_message *)ev_data;
    const char *dir = (const char *)fn_data;

    if(mg_http_match_uri(hm, ENDPOINT_STATUS))
    {
        http_reply_status(c, OK, 0);
        return;
    }

    if(mg_http_match_uri(hm, ENDPOINT_EXISTS))
    {
        http_reply(c, handle_exists(hm, dir));
        return;
    }
    
    if(mg_http_match_uri(hm, ENDPOINT_UPLOAD))
    {
        http_reply(c, handle_upload(hm, dir));
        return;
    }

    http_reply_status(c, NOT_FOUND, -1);
}