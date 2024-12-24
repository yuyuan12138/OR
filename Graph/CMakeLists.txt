cmake_minimum_required(VERSION 3.10.0)
project(Graph VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB SOURCES "src/*.cpp")

add_executable(Graph main.cpp ${SOURCES})
