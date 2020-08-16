function(copy_assets TARGET_NAME)
    add_custom_target(copy_assets_${TARGET_NAME} COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets" "${CMAKE_CURRENT_BINARY_DIR}/assets")
    add_dependencies(${TARGET_NAME} copy_assets_${TARGET_NAME})
endfunction()

add_subdirectory(playground)
add_subdirectory(snake)
