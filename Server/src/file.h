#ifndef __file_h__
#define __file_h__

#include <stdlib.h>
#include <stdint.h>
#include <mongoose.h>

#define URL_MAX_SIZE 150 // Count including \0 terminator
#define HEADER_FILE_NAME "X-File-Name"

const char *make_file_url(struct mg_http_message *hm, const char *dir);
int append_to_file(const uint8_t *data, size_t n_bytes, const char *url);

#endif