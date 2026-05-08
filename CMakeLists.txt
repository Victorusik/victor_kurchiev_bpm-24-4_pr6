cmake_minimum_required(VERSION 3.23)
project(GraphRepresentations LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(graph STATIC
        graph.cpp
        graph.h
)

target_include_directories(graph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

foreach(TASK 2 3 4)
    add_executable(task${TASK} task${TASK}.cpp)
    target_link_libraries(task${TASK} PRIVATE graph)
endforeach()
