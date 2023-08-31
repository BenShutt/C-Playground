#include <cjson/cJSON.h>
#include <stdbool.h>

#include "request.h"
#include "check.h"

void handle_request(const char *message)
{
    FileRequest *request = FileRequest_init(message);
    check(request != NULL, "Invalid request.");
    FileRequest_print(request);

error: // Fallthrough
    if(request) FileRequest_deinit(request);
}

FileRequest *FileRequest_init(const char *message)
{
    FileRequest *request = NULL;
    cJSON *json = NULL;
    check(message != NULL, "Invalid argument.");

    json = cJSON_Parse(message);
    check(json != NULL, "Invalid JSON.");

    cJSON *file_name_json = cJSON_GetObjectItemCaseSensitive(json, "file_name");
    bool file_name_rc = cJSON_IsString(file_name_json) && file_name_json->valuestring != NULL;
    check(file_name_rc, "Invalid or missing 'file_name' key.");
    char *file_name = file_name_json->valuestring; // TODO zero terminator?

    cJSON *size_json = cJSON_GetObjectItemCaseSensitive(json, "size");
    bool size_rc = cJSON_IsNumber(size_json) && size_json->valueint > 0;
    check(size_rc, "Invalid or missing 'size' key.");
    size_t size = (size_t)file_name_json->valueint;

    request = malloc(sizeof(FileRequest));
    check_memory(request);

    request->file_name = file_name;
    request->size = size;

error: // Fallthrough
    if(json) cJSON_Delete(json);
    return request;
}

void FileRequest_deinit(FileRequest *request)
{
    if(request)
    {
        if(request->file_name)
        {
            free(request->file_name); // TODO: needed?
        }
        free(request);
    }
}

void FileRequest_print(FileRequest *request)
{
    if(request != NULL)
    {
        printf("FileRequest: file_name: %s, size: %ld\n", 
            request->file_name, request->size);
    }
    else
    {
       printf("FileRequest: NULL"); 
    }
}