#include <stdlib.h>
#include <string.h>

#include "file_server.h"
#include "check.h"
#include "request_parts.h"
#include "request.h"
#include "file.h"

#define URL_SIZE 100

int write_request(Arguments *arguments, Request *request) // Private 
{    
    // Check that we can build a valid URL
    int dir_len = strnlen(arguments->dir, URL_SIZE);
    int file_name_len = strnlen(arguments->dir, URL_SIZE);
    int len = dir_len + file_name_len + sizeof('/') + sizeof('\0');
    check(len < URL_SIZE, "Invalid URL length.");

    // Compose URL from request
    char url[URL_SIZE] = { 0 };
    int rc = sprintf(url, "%s/%s", arguments->dir, request->file_name);
    check(rc > 0, "Failed to build URL.");

    // TODO: Bytes don't match xxd path/to/file
    print_hex((uint8_t *)request->data, 24);
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