cmake_minimum_required(VERSION 3.25.1)
project(reset_lines)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILE_FLAGS "-Wall" "-Werr")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GPIOD REQUIRED libgpiodcxx)

add_executable(main main.cpp)

target_link_libraries(main ${GPIOD_LIBRARIES})