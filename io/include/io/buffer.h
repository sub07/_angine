#pragma once

#include <utils/types.h>

typedef struct {
  u8 *buffer;
  u64 size;
} ByteBuffer;

ByteBuffer allocate_buffer(u64 size);
ByteBuffer allocate_buffer_value(u64 size, u8 value);
ByteBuffer allocate_buffer_zeros(u64 size);
void free_buffer(ByteBuffer buffer_to_free);

const char *str_from_buffer(ByteBuffer);
