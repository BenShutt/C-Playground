#include <stdbool.h>

#include "json_util.h"
#include "check.h"

char *read_string(cJSON *json, const char *key, size_t n_char)
{
    cJSON *child_json = cJSON_GetObjectItemCaseSensitive(json, key);
    bool rc = cJSON_IsString(child_json) && child_json->valuestring != NULL;
    check(rc, "Invalid or missing string for JSON key '%s'.", key);

    char *string = calloc(n_char, sizeof(char));
    check_memory(string);
    strlcpy(string, child_json->valuestring, n_char);
    return string;

error:
    return NULL;
}

size_t read_size(cJSON *json, const char *key)
{
    cJSON *child_json = cJSON_GetObjectItemCaseSensitive(json, key);
    bool rc = cJSON_IsNumber(child_json) && child_json->valueint >= 0;
    check(rc, "Invalid or missing size for JSON key '%s'.", key);
    return (size_t)child_json->valueint;

error:
    return -1;
}