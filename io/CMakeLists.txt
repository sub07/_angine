add_library(io buffer.c file.c include/io/buffer.h include/io/file.h)
target_include_directories(io PUBLIC include)
target_link_libraries(io utils)