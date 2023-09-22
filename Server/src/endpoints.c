#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#include "endpoints.h"
#include "check.h"
#include "file.h"

#define BOOL_STR(C) ((C) == 0 ? "false" : "true")

int handle_status()
{
    return 0;
}

int handle_exists(struct mg_http_message *hm, const char *dir)
{
    // Make URL
    char *url = (char *)make_file_url(hm, dir);
    check(url != NULL, "Failed to make URL.");

    // Check if the file exists
    int rc = access(url, F_OK) == 0;
    printf("[EXISTS] %s for '%s'.\n", BOOL_STR(rc), url);

    // Clean up and return success
    free(url);
    return rc;

error:
    return -1;
}

int handle_upload(struct mg_http_message *hm, const char *dir)
{
    // Make URL
    char *url = (char *)make_file_url(hm, dir);
    check(url != NULL, "Failed to make URL.");

    // Write HTTP body to file
    int rc = write_file((u_int8_t *)hm->body.ptr, hm->body.len, url);
    check(rc == 0, "Failed to write file.");

    // Print success
    printf("[UPLOAD] %ld bytes successfully written to '%s'.\n", hm->body.len, url);
    
    // Clean up and return success
    free(url);
    return 0;

error:
    if(url) free(url);
    return -1;
}