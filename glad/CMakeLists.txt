add_library(glad glad.c khrplatform.h include/glad/glad.h)
target_include_directories(glad PUBLIC include)