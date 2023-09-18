#include <stdio.h>

#include "file.h"
#include "check.h"

#define URL_MAX_SIZE 100

const char *make_file_url(const char *dir, const char *file_name)
{
    // Check that we can build a valid URL
    int dir_len = strnlen(dir, URL_MAX_SIZE);
    int sep_len = strnlen("/", URL_MAX_SIZE);
    int file_name_len = strnlen(file_name, URL_MAX_SIZE);
    int len = dir_len + sep_len + file_name_len;
    check(len < URL_MAX_SIZE, "Invalid URL length.");

    // Allocate memory to URL - allowing space for the null terminator
    char *url = malloc((len + 1) * sizeof(char));
    check_memory(url);
    
    // Compose URL from request
    int rc = sprintf(url, "%s/%s", dir, file_name);
    check(rc > 0, "Failed to build URL.");

    // Ensure terminating null byte is set
    url[len] = '\0';
    return url;

error:
    return NULL;
}

int write_file(const uint8_t *data, size_t n_bytes, const char *url)
{
    // Pointers to free on error
    FILE *file = NULL;

    // Check arguments are valid
    check(data != NULL, "Invalid data argument.");
    check(n_bytes >= 0, "Invalid n_bytes argument.");
    check(url != NULL, "Invalid url argument.");

    // Open binary file for writing
    file = fopen(url, "wb");
    check(file != NULL, "Failed to open file '%s'.", url);

    // Write bytes to file
    fwrite(data, sizeof(uint8_t), n_bytes, file);
    check(ferror(file) == 0, "Failed to write file '%s'.", url);

    // Close and exit with success
    fclose(file);
    return 0;

error:
    if(file) fclose(file);
    return -1;
}