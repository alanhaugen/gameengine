cmake_minimum_required(VERSION 3.19)
project(AAPhysics LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(AAPhysics STATIC
    aaphysics.cpp
    aaphysics.h
)

target_include_directories(AAPhysics PRIVATE ../../../../include)
