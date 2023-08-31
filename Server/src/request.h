#ifndef __request_h__
#define __request_h__

#include <stdlib.h>

typedef struct FileRequest {
    char *file_name;
    size_t size;
} FileRequest;

FileRequest *FileRequest_init(const char *json);
void FileRequest_deinit(FileRequest *request);
void FileRequest_print(FileRequest *request);

#endif