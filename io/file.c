#include <io/file.h>
#include <stdio.h>
#include <assert.h>

u64 get_file_size(FILE *f) {
  rewind(f);
  fseek(f, 0, SEEK_END);
  return ftell(f);
}

byte_buffer buffer_from_file(const char *path) {
  FILE *f = fopen(path, "rb");
  u64 size = get_file_size(f);
  byte_buffer buf = allocate_buffer(size);
  rewind(f);
#ifndef NDEBUG
  i32 read = fread(buf.buffer, 1, size, f);
  assert(read == size);
#else
  fread(buf.buffer, 1, size, f);
#endif
  return buf;
}

