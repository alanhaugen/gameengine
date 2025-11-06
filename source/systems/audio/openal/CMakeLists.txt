cmake_minimum_required(VERSION 3.19)
project(OpenALAudio LANGUAGES CXX)

add_library(OpenALAudio STATIC
    openalaudio.cpp
    openalaudio.h
    soundsource.cpp
    soundsource.h
    wavfilereader.cpp
    wavfilereader.h
)

target_include_directories(OpenALAudio PRIVATE ../../../../include)
