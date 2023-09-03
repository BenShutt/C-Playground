#include <stdlib.h>
#include <string.h>

#include "file_server.h"
#include "check.h"
#include "request_parts.h"
#include "request.h"
#include "file.h"

int write_request(Arguments *arguments, Request *request) // Private 
{    
    char url[100] = { 0 }; // TODO: Ought to error if this will not be enough
    int rc = sprintf(url, "%s/%s", arguments->dir, request->file_name);
    check(rc > 0, "Failed to build URL.");
    return write_file((uint8_t *)request->data, request->size, url);

error:
    return -1;
}

char *file_server_handle(Arguments *arguments, const char *message)
{
    RequestParts *request_parts = NULL;
    Request *request = NULL;
    check(message != NULL, "Invalid argument.");
    
    request_parts = RequestParts_init(message);
    check(request_parts != NULL, "Failed to initialize RequestParts.");

    request = Request_init(request_parts);
    check(request != NULL, "Failed to initialize Request."); 
    Request_print(request);

    int rc = write_request(arguments, request);
    check(rc == 0, "Failed to write file.");
    
    Request_deinit(request);
    RequestParts_deinit(request_parts);
    return "Success";

error:
    if(request) Request_deinit(request);
    if(request_parts) RequestParts_deinit(request_parts);
    return "Error";
}