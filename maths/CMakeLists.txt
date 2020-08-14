add_library(maths matrix.c utils.c vec.c include/maths/matrix.h include/maths/vec.h include/maths/utils.h)
target_include_directories(maths PUBLIC include)