cmake_minimum_required(VERSION 3.19)
project(NullPhysics LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(NullPhysics STATIC
    nullphysics.cpp
    nullphysics.h
)

target_include_directories(NullPhysics PRIVATE ../../../../include)
