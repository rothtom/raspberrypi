project(led)

cmake_minimum_required(VERSION 3.25.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

add_executable(led led.cpp)

target_link_libraries(led pigpio)
