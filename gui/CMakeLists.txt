cmake_minimum_required(VERSION 3.13)

# required packages
#find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

#download and build glew
configure_file(CMakeLists.txt.in glfw-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/glfw-download )
if(result)
  message(FATAL_ERROR "CMake step for glfw failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/glfw-download )
if(result)
  message(FATAL_ERROR "Build step for glfw failed: ${result}")
endif()

#add dir
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/glfw-src
                 ${CMAKE_CURRENT_BINARY_DIR}/glfw-build
                 EXCLUDE_FROM_ALL)

add_executable(gbadbg-gui main.cpp)

# compile imgui
file(GLOB_RECURSE IMGUI_SOURCES "${PROJECT_SOURCE_DIR}/gui/imgui/*.cpp")
target_sources(gbadbg-gui PRIVATE ${IMGUI_SOURCES})

#link libs
target_link_libraries(gbadbg-gui gbadbg-emu)
target_link_libraries(gbadbg-gui glfw)
target_link_libraries(gbadbg-gui OpenGL::GL)