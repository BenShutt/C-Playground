#include <stdio.h>

#include "file.h"
#include "check.h"

int write_file(uint8_t bytes[], size_t size, const char *url)
{
    FILE *file = NULL;
    check(url != NULL, "Invalid argument.");

    file = fopen(url, "wb");
    check(file != NULL, "Failed to open file '%s'.", url);

    size_t rc = fwrite(bytes, size, 1, file);
    check(rc >= 1, "Failed to write to file '%s'.", url);

    fclose(file);
    return 0;

error:
    if(file) fclose(file);
    return -1;
}