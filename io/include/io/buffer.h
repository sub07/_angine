#pragma once

#include <utils/types.h>

typedef struct {
  u8 *buffer;
  u64 size;
} byte_buffer;

byte_buffer allocate_buffer(u64 size);
byte_buffer allocate_buffer_value(u64 size, u8 value);
byte_buffer allocate_buffer_zeros(u64 size);
void free_buffer(byte_buffer buffer_to_free);

const char *str_from_buffer(byte_buffer);