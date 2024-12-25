cmake_minimum_required(VERSION 3.10.0)
project(Graph VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB SOURCES "src/*.cpp")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_executable(Graph main.cpp ${SOURCES})

add_library(
        Graph
        ${SOURCES}
)

target_include_directories(Graph PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

install(TARGETS Graph
        EXPORT GraphTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)

install(EXPORT GraphTargets
        FILE GraphTargets.cmake
        NAMESPACE Graph::
        DESTINATION lib/cmake/Graph
)
