#include "request.h"
#include "check.h"

FileRequest *FileRequest_init(char *json)
{
    check(json != NULL, "Invalid argument");

    FileRequest *request = malloc(sizeof(FileRequest));
    check_memory(request);

    request->file_name = NULL;
    request->size = 0;
    return request;

error:
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