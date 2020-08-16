add_library(utils INTERFACE)
target_include_directories(utils SYSTEM INTERFACE include)

add_library(collection include/collection/hash_table.h hash_table.c include/collection/hash_table.h hash_table.c)
target_include_directories(collection PUBLIC include)
