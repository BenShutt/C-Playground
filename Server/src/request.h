#ifndef __request_h__
#define __request_h__

#include <stdlib.h>

typedef struct FileRequest {
    char *file_name;
    size_t size;
} FileRequest;

FileRequest *FileRequest_init(char *json);
void FileRequest_deinit(FileRequest *request);

#endif