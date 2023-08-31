#ifndef __json_util_h__
#define __json_util_h__

#include <stdlib.h>
#include <cjson/cJSON.h>

char *read_string(cJSON *json, const char *key, size_t n_char);
size_t read_size(cJSON *json, const char *key);

#endif