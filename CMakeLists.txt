cmake_minimum_required(VERSION 3.5)
project(glut)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_EXE_LINKER_FLAGS "-static")


set(SOURCE_FILES main.cpp Fireworks2D.cpp Fireworks2D.h)
add_executable(glut ${SOURCE_FILES})

target_link_libraries(glut libopengl32.a libglu32.a libfreeglut.a)