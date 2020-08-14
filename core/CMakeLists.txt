add_library(core include/core/angine.h include include/core/key.h angine.c batch.h glfw.h include/core/scene.h shader.h utils.h utils.c window.c window.h include/core/color.h color.c)
target_include_directories(core PUBLIC include)
target_link_libraries(core PRIVATE glfw)
target_link_libraries(core PUBLIC maths utils)