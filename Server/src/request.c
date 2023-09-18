#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#include "request.h"
#include "check.h"
#include "mongoose_extensions.h"
#include "file.h"

#define BOOL_STR(C) ((C) == 0 ? "false" : "true")

static const char *make_url(struct mg_http_message *hm, const char *dir)
{
    // Pointers to free on error
    char *file_name = NULL;

    // Get the file name from the custom HTTP header
    struct mg_str *file_name_str = mg_http_get_header(hm, HEADER_FILE_NAME);
    check(file_name_str != NULL, "Missing '%s' HTTP header.", HEADER_FILE_NAME);

    // Map to C string
    file_name = (char *)c_str(*file_name_str);
    check(file_name != NULL, "Failed to map to C string.");

    // Make URL
    const char *url = (char *)make_file_url(dir, file_name);
    check(url != NULL, "Failed to make URL.");

    // Clean up and return success
    free(file_name);
    return url;

error:
    if(file_name) free(file_name);
    return NULL;
}

static int handle_exists(struct mg_http_message *hm, const char *dir)
{
    // Make URL
    char *url = (char *)make_url(hm, dir);
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
    char *url = (char *)make_url(hm, dir);
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

static void http_reply_status_code(struct mg_connection *c, int rc)
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
        http_reply_status_code(c, handle_exists(hm, dir));
        return;
    }
    
    if(mg_http_match_uri(hm, ENDPOINT_UPLOAD))
    {
        http_reply_status_code(c, handle_upload(hm, dir));
        return;
    }

    http_reply_status(c, NOT_FOUND, 0);
}