cmake_minimum_required(VERSION 3.13)
project(gbadbg)

enable_testing()

add_subdirectory(emu)
add_subdirectory(gui)
add_subdirectory(tests)