cmake_minimum_required(VERSION 3.15)
project(miniquery)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC_FILES src/*.cpp)
file(GLOB HEADER_FILES include/*.h)

find_package(Arrow REQUIRED)

add_executable(neutrino ${SRC_FILES})

target_include_directories(neutrino PRIVATE include)
target_link_libraries(neutrino PRIVATE Arrow::arrow_shared)