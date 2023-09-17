#include <stdio.h>
#include <stdint.h>

#include "request.h"
#include "check.h"
#include "file.h"

#define ENDPOINT_STATUS "/api/status"
#define ENDPOINT_UPLOAD "/api/upload"

#define NL "\r\n"
#define HEADER_FILE_NAME "X-File-Name"
#define URL_MAX_SIZE 100

typedef enum HTTP_Status_Code { // TODO: Naming convention
    OK = 200,
    BAD_REQUEST = 400,
    NOT_FOUND = 404
} HTTP_Status_Code;

static char *make_url(struct mg_http_message *hm, const char *dir)
{
    // Get the file name from the custom HTTP header
    struct mg_str *file_name = mg_http_get_header(hm, HEADER_FILE_NAME);
    check(file_name != NULL, "Missing '%s' HTTP header.", HEADER_FILE_NAME);

    // Check that we can build a valid URL
    int dir_len = strnlen(dir, URL_MAX_SIZE);
    int len = dir_len + file_name->len + strlen("/");
    check(len < URL_MAX_SIZE, "Invalid URL length.");

    // Allocate memory to URL - allowing space for the null terminator
    char *url = malloc((len + 1) * sizeof(char));
    check_memory(url);
    
    // Compose URL from request
    int rc = sprintf(url, "%s/%.*s", dir, (int)file_name->len, file_name->ptr);
    check(rc > 0, "Failed to build URL.");

    // Ensure terminating null byte is set
    url[len] = '\0';
    return url;

error:
    return NULL;
}

static int handle_upload(struct mg_http_message *hm, const char *dir)
{
    char *url = make_url(hm, dir);
    check(url != NULL, "Failed to make URL.");

    printf("Writing to '%s'\n", url);
    print_hex((u_int8_t *)hm->body.ptr, 24);
    
    free(url);
    return 0;

error:
    if(url) free(url);
    return -1;
}

void http_reply_status(struct mg_connection *c, HTTP_Status_Code status_code, int status)
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