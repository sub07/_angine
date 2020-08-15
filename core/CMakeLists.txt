add_library(core
        include/core/angine.h
        include include/core/key.h
        angine.c
        glfw.h
        include/core/scene.h
        shader.h
        utils.h
        utils.c
        window.c
        window.h
        include/core/color.h
        color.c
        include/core/image.h
        image.c
        include/core/texture.h
        texture.c
        shader_sources.h
        shader_sources.c
        mesh.h
        mesh.c include/core/texture_batch.h texture_batch.h texture_batch.c texture.h shader.c)

target_include_directories(core PUBLIC include)
target_link_libraries(core PRIVATE glfw graphics)
target_link_libraries(core PUBLIC maths utils)
