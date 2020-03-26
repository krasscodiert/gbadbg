cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)

# required packages
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(gbadbg-gui main.cpp)

# compile imgui
file(GLOB_RECURSE IMGUI_SOURCES "${PROJECT_SOURCE_DIR}/gui/imgui/*.cpp")
target_sources(gbadbg-gui PRIVATE ${IMGUI_SOURCES})

#link libs
#target_link_libraries(gbadbg-gui gbadbg-emu)
target_link_libraries(gbadbg-gui glfw)
target_link_libraries(gbadbg-gui OpenGL::GL)