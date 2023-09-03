#ifndef __file_h__
#define __file_h__

#include <stdlib.h>
#include <stdint.h>

int write_file(const uint8_t *data, size_t n_char, const char *url);
uint8_t *read_file(size_t n_char, const char *url);
void print_hex(uint8_t *buf, size_t n);

#endif