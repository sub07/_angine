#include <io/buffer.h>
#include <stdlib.h>
#include <string.h>

ByteBuffer allocate_buffer(u64 size) {
  ByteBuffer ret;
  ret.buffer = malloc(size + 1);
  ret.size = size;
  return ret;
}

ByteBuffer allocate_buffer_value(u64 size, u8 value) {
  ByteBuffer ret;
  ret.buffer = malloc(size + 1);
  memset(ret.buffer, value, size);
  ret.size = size;
  return ret;
}

ByteBuffer allocate_buffer_zeros(u64 size) {
  ByteBuffer ret;
  ret.buffer = calloc(size + 1, 1);
  ret.size = size;
  return ret;
}

void free_buffer(ByteBuffer buffer) {
  free(buffer.buffer);
}

const char *str_from_buffer(ByteBuffer buffer) {
  buffer.buffer[buffer.size] = '\0';
  return (const char *) buffer.buffer;
}

