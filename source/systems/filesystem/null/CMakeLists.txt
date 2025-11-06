cmake_minimum_required(VERSION 3.19)
project(NullFileSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(NullFileSystem STATIC
    nullfilesystem.cpp
    nullfilesystem.h
)

target_include_directories(NullFileSystem PRIVATE ../../../../include)
