cmake_minimum_required(VERSION 3.19)
project(NullAudio LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(NullAudio STATIC
    nullaudio.cpp
    nullaudio.h
)

target_include_directories(NullAudio PRIVATE ../../../../include)
