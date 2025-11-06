cmake_minimum_required(VERSION 3.19)
project(RPG LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(RPG
    CMakeLists.txt
    source/main.cpp
)

#target_link_libraries(Demos PRIVATE
#target_compile_options(Demos PRIVATE /EHsc)
#target_include_directories(Demos PRIVATE
