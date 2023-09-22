#include <stdio.h>

#include "file.h"
#include "check.h"
#include "mongoose_extensions.h"

static const char *make_url(const char *dir, const char *file_name)
{
    char *url = NULL;

    // Check arguments are valid
    check(dir != NULL, "Invalid dir argument.");
    check(file_name != NULL, "Invalid file_name argument.");

    // Check that we can build a valid URL
    int dir_len = strnlen(dir, URL_MAX_SIZE);
    int sep_len = strnlen("/", URL_MAX_SIZE);
    int file_name_len = strnlen(file_name, URL_MAX_SIZE);
    int len = dir_len + sep_len + file_name_len;
    check(len < URL_MAX_SIZE, "Invalid URL length.");

    // Allocate memory to URL - allowing space for the null terminator
    url = malloc((len + 1) * sizeof(char));
    check_memory(url);
    
    // Compose URL from request
    int rc = sprintf(url, "%s/%s", dir, file_name);
    check(rc > 0, "Failed to build URL.");

    // Ensure terminating null byte is set
    url[len] = '\0';
    return url;

error:
    if(url) free(url);
    return NULL;
}

const char *make_file_url(struct mg_http_message *hm, const char *dir)
{
    // Pointers to free on error
    char *file_name = NULL;

    // Get the file name from the custom HTTP header
    struct mg_str *file_name_str = mg_http_get_header(hm, HEADER_FILE_NAME);
    check(file_name_str != NULL, "Missing '%s' HTTP header.", HEADER_FILE_NAME);

    // Map to C string
    file_name = (char *)c_str(*file_name_str);
    check(file_name != NULL, "Failed to map to C string.");

    // Make URL
    const char *url = (char *)make_url(dir, file_name);
    check(url != NULL, "Failed to make URL.");

    // Clean up and return success
    free(file_name);
    return url;

error:
    if(file_name) free(file_name);
    return NULL;
}

int append_file(const uint8_t *data, size_t n_bytes, const char *url)
{
    // Pointers to free on error
    FILE *file = NULL;

    // Check arguments are valid
    check(data != NULL, "Invalid data argument.");
    check(n_bytes >= 0, "Invalid n_bytes argument.");
    check(url != NULL, "Invalid url argument.");

    // Open binary file for appending
    file = fopen(url, "ab");
    check(file != NULL, "Failed to open file '%s'.", url);

    // Append bytes to file
    fwrite(data, sizeof(uint8_t), n_bytes, file);
    check(ferror(file) == 0, "Failed to append to file '%s'.", url);

    // Close and exit with success
    fclose(file);
    return 0;

error:
    if(file) fclose(file);
    return -1;
}