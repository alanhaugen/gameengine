cmake_minimum_required(VERSION 3.19)
project(NullScript LANGUAGES CXX)

add_library(NullScript STATIC
    nullscript.h
    nullscript.cpp
)
