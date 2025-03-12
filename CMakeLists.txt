cmake_minimum_required(VERSION 3.30.1)
project(SnakeOGL VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

add_executable(snake-cpp 
    src/main.cpp 
    )

target_include_directories(snake-cpp PUBLIC vendor)

target_link_libraries(snake-cpp SDL3::SDL3)