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

target_link_libraries(OpenALAudio PRIVATE $ENV{OPENAL_HOME}/libs/Win64/OpenAL32.lib)

target_include_directories(OpenALAudio PRIVATE ../../../../include)
