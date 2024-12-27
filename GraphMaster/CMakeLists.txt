cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
project(GraphMaster VERSION 1.0)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)

# 目录包含其他 CMake 模块
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/lib/cxxopts")

# 添加头文件路径
include_directories(include)
include_directories(lib/cxxopts/include)  # cxxopts 头文件路径

file(GLOB SOURCES "src/*.cpp")

#file(GLOB CXXOPTS_SOURCES "lib/cxxopts/src/*.cpp")  # 假设 cxxopts 的 cpp 文件在 src 子目录中
#list(APPEND SOURCES ${CXXOPTS_SOURCES})


add_executable(GrapherMaster main.cpp ${SOURCES})

#target_link_libraries(GraphMaster PRIVATE cxxopts::cxxopts)
