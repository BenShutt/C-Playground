#include <cjson/cJSON.h>

#include "request.h"
#include "check.h"

FileRequest *FileRequest_init(const char *message)
{
    cJSON *json = NULL;
    check(message != NULL, "Invalid argument");

    json = cJSON_Parse(message);

    FileRequest *request = malloc(sizeof(FileRequest));
    check_memory(request);

    request->file_name = NULL;
    request->size = 0;

    if(json) cJSON_Delete(json);
    return request;

error:
    if(json) cJSON_Delete(json);
    return NULL;
}

void FileRequest_deinit(FileRequest *request)
{
    if(request)
    {
        if(request->file_name)
        {
            free(request->file_name);
        }
        free(request);
    }
}