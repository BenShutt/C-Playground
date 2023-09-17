#include <stdio.h>

#include "file.h"
#include "check.h"

int write_file(const uint8_t *data, size_t n_bytes, const char *url)
{
    FILE *file = NULL;
    check(data != NULL, "Invalid data argument.");
    check(n_bytes >= 0, "Invalid n_bytes argument.");
    check(url != NULL, "Invalid url argument.");

    file = fopen(url, "wb");
    check(file != NULL, "Failed to open file '%s'.", url);

    fwrite(data, sizeof(uint8_t), n_bytes, file);
    check(ferror(file) == 0, "Failed to write file '%s'.", url);

    fclose(file);
    return 0;

error:
    if(file) fclose(file);
    return -1;
}

uint8_t *read_file(size_t n_bytes, const char *url)
{
    FILE *file = NULL;
    uint8_t *buf = NULL;
    check(n_bytes >= 0, "Invalid n_bytes argument.");
    check(url != NULL, "Invalid url argument.");

    file = fopen(url, "rb");
    check(file != NULL, "Failed to open file '%s'.", url);
    
    int rc = fseek(file, 0, SEEK_SET);
    check(rc == 0, "Failed to seek file '%s'.", url);

    buf = malloc(sizeof(uint8_t) * n_bytes);
    check_memory(buf);

    fread(buf, sizeof(uint8_t), n_bytes, file);
    check(ferror(file) == 0, "Failed to read file '%s'.", url);

    fclose(file);
    return buf;

error:
    if(buf) free(buf);
    if(file) fclose(file);
    return NULL;
}

void print_hex(uint8_t *buf, size_t n)
{
    if(n <= 0) return;

    for(size_t i = 0; i < n; i++)
        printf("%02x", buf[i]);
    
    printf("\n");
}