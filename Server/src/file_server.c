#include "file_server.h"
#include "check.h"
#include "request_parts.h"
#include "request.h"

int write_request(Request *request) // Private 
{
    Request_print(request);
    return 0;
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