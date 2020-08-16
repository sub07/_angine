#pragma once

typedef int(*HashFunc)(void *);

typedef struct {
  void *table;
  int capacity;
  HashFunc hash_func;
} HashTable;
