cmake_minimum_required(VERSION 3.13)

file(GLOB_RECURSE EMU_SOURCES "${PROJECT_SOURCE_DIR}/emu/*.h" "${PROJECT_SOURCE_DIR}/emu/*.cpp")

message(STATUS ${EMU_SOURCES})

add_library(gbadbg-emu ${EMU_SOURCES})