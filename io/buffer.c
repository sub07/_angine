#include <io/buffer.h>
#include <stdlib.h>
#include <string.h>

byte_buffer allocate_buffer(u64 size) {
  byte_buffer ret;
  ret.buffer = malloc(size + 1);
  ret.size = size;
  return ret;
}

byte_buffer allocate_buffer_value(u64 size, u8 value) {
  byte_buffer ret;
  ret.buffer = malloc(size + 1);
  memset(ret.buffer, value, size);
  ret.size = size;
  return ret;
}

byte_buffer allocate_buffer_zeros(u64 size) {
  byte_buffer ret;
  ret.buffer = calloc(size + 1, 1);
  ret.size = size;
  return ret;
}

void free_buffer(byte_buffer buffer) {
  free(buffer.buffer);
}

const char *str_from_buffer(byte_buffer buffer) {
  buffer.buffer[buffer.size] = '\0';
  return (const char *) buffer.buffer;
}

