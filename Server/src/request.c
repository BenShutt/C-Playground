#include <cjson/cJSON.h>
#include <string.h>

#include "request.h"
#include "check.h"
#include "json_util.h"

// Number of characters supported by file_name (including NUL-terminator)
#define FILE_NAME_COUNT 100

Request *Request_init(RequestParts *request_parts)
{
    // Pointers to free on error
    cJSON *json = NULL;
    char *file_name = NULL;

    // Parse the argument into JSON
    json = cJSON_Parse(request_parts->json);
    check(json != NULL, "Invalid JSON.");

    // Extract file_name string from JSON
    file_name = read_string(json, "file_name", FILE_NAME_COUNT);
    check(file_name != NULL, "Failed to parse 'file_name' JSON key.");
    
    // Extract size int from JSON
    size_t size = read_size(json, "size");
    check(size >= 0, "Failed to parse 'size' JSON key.");
    
    // Only take the relevant first n bytes
    int rc = RequestParts_trim_data(request_parts, size);
    check(rc == 0, "Failed to trim data.");

    // Make request to return 
    Request *request = malloc(sizeof(Request));
    check_memory(request);
    request->file_name = file_name;
    request->size = size;
    request->data = request_parts->data;

    // Free JSON and return with success
    cJSON_Delete(json);
    return request;

error:
    if(file_name) free(file_name);
    if(json) cJSON_Delete(json);
    return NULL;
}

void Request_deinit(Request *request)
{
    if(request)
    {
        if(request->file_name)
            free(request->file_name);

        free(request);
    }
}

void Request_print(Request *request)
{
    if(request)
    {
        printf("Request: file_name: %s, size: %ld\n", 
            request->file_name, request->size);
    }
    else
    {
       printf("Request: NULL"); 
    }
}