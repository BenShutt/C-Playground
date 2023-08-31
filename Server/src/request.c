#include <cjson/cJSON.h>

#include "request.h"
#include "check.h"
#include "json_util.h"

// Number of characters supported by file_name (including NUL-terminator)
#define FILE_NAME_COUNT 100

FileRequest *FileRequest_init(const char *message)
{
    // Pointers to free on error
    cJSON *json = NULL;
    char *file_name = NULL;
    
    // Check the argument is valid
    check(message != NULL, "Invalid argument.");

    // Parse the argument into JSON
    json = cJSON_Parse(message);
    check(json != NULL, "Invalid JSON.");

    // Extract file_name string from JSON
    file_name = read_string(json, "file_name", FILE_NAME_COUNT);
    check(file_name != NULL, "Failed to parse 'file_name' JSON key.");
    
    // Extract size int from JSON
    size_t size = read_size(json, "size");
    check(size >= 0, "Failed to parse 'size' JSON key.");

    // Make request to return 
    FileRequest *request = malloc(sizeof(FileRequest));
    check_memory(request);
    request->file_name = file_name;
    request->size = size;

    // Free JSON and return with success
    cJSON_Delete(json);
    return request;

error:
    if(file_name) free(file_name);
    if(json) cJSON_Delete(json);
    return NULL;
}

void FileRequest_deinit(FileRequest *request)
{
    if(request)
    {
        if(request->file_name)
            free(request->file_name);

        free(request);
    }
}

void FileRequest_print(FileRequest *request)
{
    if(request)
    {
        printf("FileRequest: file_name: %s, size: %ld\n", 
            request->file_name, request->size);
    }
    else
    {
       printf("FileRequest: NULL"); 
    }
}