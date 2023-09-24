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
    printf("[STATUS] success.\n");
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

int handle_upload(struct mg_http_message *hm, struct mg_str data, const char *dir, bool is_end)
{
    // Make URL
    char *url = (char *)make_file_url(hm, dir);
    check(url != NULL, "Failed to make URL.");

    if(is_end)
    {
        // Log success at end
        printf("[UPLOAD] successfully written to '%s'.\n", url);
    }
    else
    {
        // Write HTTP body to file
        int rc = append_file((u_int8_t *)data.ptr, data.len, url);
        check(rc == 0, "Failed to write file.");
    }
    
    // Clean up and return success
    free(url);
    return 0;

error:
    if(url) free(url);
    return -1;
}