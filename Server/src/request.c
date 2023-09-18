#include <stdio.h>
#include <stdint.h>

#include "request.h"
#include "check.h"
#include "mongoose_extensions.h"
#include "file.h"

#define ENDPOINT_STATUS "/api/status"
#define ENDPOINT_UPLOAD "/api/upload"

#define NL "\r\n"
#define HEADER_FILE_NAME "X-File-Name"

typedef enum StatusCode {
    OK = 200,
    BAD_REQUEST = 400,
    NOT_FOUND = 404
} StatusCode;

static int handle_upload(struct mg_http_message *hm, const char *dir)
{
    // Pointers to free on error
    char *file_name = NULL;
    char *url = NULL;

    // Get the file name from the custom HTTP header
    struct mg_str *file_name_str = mg_http_get_header(hm, HEADER_FILE_NAME);
    check(file_name_str != NULL, "Missing '%s' HTTP header.", HEADER_FILE_NAME);

    // Map to C string
    file_name = (char *)c_str(*file_name_str);
    check(file_name != NULL, "Failed to map to C string.");

    // Make URL
    url = (char *)make_file_url(dir, file_name);
    check(url != NULL, "Failed to make URL.");

    // Write HTTP body to file
    write_file((u_int8_t *)hm->body.ptr, hm->body.len, url);
    printf("%ld bytes successfully written to '%s'\n", hm->body.len, url);
    
    // Clean up and return success
    free(url);
    free(file_name);
    return 0;

error:
    if(url) free(url);
    if(file_name) free(file_name);
    return -1;
}

void http_reply_status(struct mg_connection *c, StatusCode status_code, int status)
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
    
    if(mg_http_match_uri(hm, ENDPOINT_UPLOAD))
    {
        int rc = handle_upload(hm, dir);
        int status_code = rc == 0 ? OK : BAD_REQUEST;
        http_reply_status(c, status_code, rc);
        return;
    }

    http_reply_status(c, NOT_FOUND, 0);
}