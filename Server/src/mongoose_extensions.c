#include <string.h>

#include "mongoose_extensions.h"
#include "check.h"

const char *c_str(struct mg_str str)
{
    char *target = malloc(str.len + sizeof('\0'));
    check_memory(target);
    strncpy(target, str.ptr, str.len);
    target[str.len] = '\0';
    return target;

error:
    return NULL;
}