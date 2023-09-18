#ifndef __file_h__
#define __file_h__

#include <stdlib.h>
#include <stdint.h>

const char *make_file_url(const char *dir, const char *file_name);
int write_file(const uint8_t *data, size_t n_bytes, const char *url);

#endif