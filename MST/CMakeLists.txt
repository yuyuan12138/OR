cmake_minimum_required(VERSION 3.30)
project(MST)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.cpp")

add_subdirectory(libs/Graph)


add_executable(MST main.cpp ${SOURCES})

target_link_libraries(MST PRIVATE Graph)
