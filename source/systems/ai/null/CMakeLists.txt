cmake_minimum_required(VERSION 3.19)
project(NullAI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(NullAI STATIC
    nullai.cpp
    nullai.h
)

target_include_directories(NullAI PRIVATE ../../../../include)
