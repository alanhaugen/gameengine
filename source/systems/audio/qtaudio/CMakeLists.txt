cmake_minimum_required(VERSION 3.19)
project(QtMultimediaAudio LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(QtMultimediaAudio STATIC
    qtmultimediaaudio.cpp
    qtmultimediaaudio.h
)

#find_package(Qt6 REQUIRED COMPONENTS Multimedia)

# target_link_libraries(QtMultimediaAudio PRIVATE
#     Qt::Multimedia
# )

target_include_directories(QtMultimediaAudio PRIVATE ../../../../include)
