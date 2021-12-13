cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(timeManager LANGUAGES C)
add_library(funcs 
STATIC
    src/libs/param.h
    src/libs/structures.h
    src/libs/linked.c
    src/libs/time.c
    src/libs/control.c
    src/libs/interface.c
    src/libs/initialize.c
    src/libs/menu.c
    src/libs/logs.c)
add_executable(teste src/main.c)
target_link_libraries(teste funcs)
target_link_libraries(teste ncurses)