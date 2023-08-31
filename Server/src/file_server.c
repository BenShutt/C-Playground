#include "file_server.h"
#include "check.h"
#include "request_parts.h"
#include <string.h>

#include "request.h"
#include "check.h"
#include "file.h"

#define URL_PREFIX "/Users/benshutt/Desktop"

int write_request(Request *request) // Private 
{
    check(URL_PREFIX != NULL, "URL prefix.");
    
    char url[100];
    int rc = sprintf(url, "%s/%s", URL_PREFIX, request->file_name);
    check(rc > 0, "Failed to build URL.");

    return write_file((uint8_t *)request->data, request->size, url); // TODO

error:
    return -1;
}

char *file_server_handle(const char *message)
{
    RequestParts *request_parts = NULL;
    Request *request = NULL;
    check(message != NULL, "Invalid argument.");
    
    request_parts = RequestParts_init(message);
    check(request_parts != NULL, "Failed to initialize RequestParts.");

    request = Request_init(request_parts);
    check(request != NULL, "Failed to initialize Request."); 
    Request_print(request);

    int rc = write_request(request);
    check(rc == 0, "Failed to write file.");
    
    Request_deinit(request);
    RequestParts_deinit(request_parts);
    return "Success";

error:
    if(request) Request_deinit(request);
    if(request_parts) RequestParts_deinit(request_parts);
    return "Error";
}