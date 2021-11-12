cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(timeManager LANGUAGES C)
add_library(funcs 
STATIC
    param.h
    time.c
    control.c
    interface.c
    initialize.c)
add_executable(teste Programa.c)
target_link_libraries(teste funcs)
target_link_libraries(teste ncurses)