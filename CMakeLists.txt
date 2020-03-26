cmake_minimum_required(VERSION 3.13)

project(gbadbg CXX)
set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(gui)
add_subdirectory(emu)
add_subdirectory(tests)