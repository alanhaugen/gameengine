cmake_minimum_required(VERSION 3.19)
project(NullRenderer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(NullRenderer STATIC
    nullrenderer.cpp
    nullrenderer.h
    ../renderer.h
)

target_include_directories(NullRenderer PRIVATE ../../../../include)
