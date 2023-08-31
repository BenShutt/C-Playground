#include <string.h>

#include "request_parts.h"
#include "check.h"

// String that separates request body content
#define SEPARATOR "\n"

RequestParts *RequestParts_init(const char *message)
{
    char *json = NULL;
    char *data = NULL;

    // Pointer that is shifted by strsep
    char *token = (char *)message;

    // Get JSON from first part of the message 
    json = strdup(strsep(&token, SEPARATOR));
    check(json != NULL, "Failed to split JSON component");

    // Get file data from second part of the message
    data = strdup(token);
    check(data != NULL, "Failed to split data component");

    // Make request to return 
    RequestParts *requestParts = malloc(sizeof(RequestParts));
    check_memory(requestParts);
    requestParts->json = json;
    requestParts->data = data;

    return requestParts;

error:
    if(data) free(data);
    if(json) free(json);
    return NULL;
}

void RequestParts_deinit(RequestParts *request_parts)
{
    if(request_parts)
    {
        if(request_parts->json)
            free(request_parts->json);

        if(request_parts->data)
            free(request_parts->data);

        free(request_parts);
    }
}