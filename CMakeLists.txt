cmake_minimum_required(VERSION 3.30.1)
project(SnakeOGL VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(snake-cpp 
    src/main.cpp 
    src/glad.c
    )

target_include_directories(snake-cpp PRIVATE dependencies)

target_link_libraries(snake-cpp glfw3 OpenGL::GL)