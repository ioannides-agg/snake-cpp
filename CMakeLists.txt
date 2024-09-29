cmake_minimum_required(VERSION 3.30.1)
project(SnakeOGL VERSION 1.0.0)

add_executable(snake-cpp src/main.cpp)

target_include_directories(snake-cpp PRIVATE dependencies)

target_link_libraries(snake-cpp glfw3)