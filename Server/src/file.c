#include <stdio.h>

#include "file.h"
#include "check.h"

int write_file(const void *data, size_t size, const char *url)
{
    FILE *file = NULL;
    check(data != NULL, "Invalid bytes argument.");
    check(url != NULL, "Invalid url argument.");

    file = fopen(url, "wb");
    check(file != NULL, "Failed to open file '%s'.", url);

    size_t rc = fwrite(data, size, 1, file);
    check(rc >= 1, "Failed to write to file '%s'.", url);

    fclose(file);
    return 0;

error:
    if(file) fclose(file);
    return -1;
}