add_executable(playground main.c ../snake/main.c)
target_link_libraries(playground core)
copy_assets(playground)
