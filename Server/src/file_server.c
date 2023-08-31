#include "file_server.h"
#include "request.h"

void write_request(FileRequest *request) // Private 
{
    FileRequest_print(request);
}

char *file_server_handle(const char *message)
{
    static FileRequest *last_request = NULL;

    if(last_request)
    {
        write_request(last_request);
        FileRequest_deinit(last_request);
        last_request = NULL;
        return "Written";
    }
    else
    {
        last_request = FileRequest_init(message);
        return last_request != NULL ? "Parsed" : "Invalid";      
    }
}