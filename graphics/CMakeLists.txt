add_library(graphics graphics.c include/graphics/graphics.h)
target_include_directories(graphics PUBLIC include)
target_link_libraries(graphics PRIVATE glad)
