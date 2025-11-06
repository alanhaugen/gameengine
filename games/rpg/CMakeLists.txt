cmake_minimum_required(VERSION 3.19)
project(RPG LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Multimedia)

qt_standard_project_setup()

add_executable(RPG
    CMakeLists.txt
    source/main.cpp
)

target_link_libraries(RPG PRIVATE
    Qt::Core
    Qt::Widgets
    Qt::Multimedia
    Core # The inn game engine

    NullAI
    NullAudio
    NullFileSystem
    NullPhysics
    NullRenderer
    NullScript

    VulkanRenderer
    AAPhysics
    QtMultimediaAudio
)

target_include_directories(RPG PRIVATE "../../source")
target_include_directories(RPG PRIVATE "../../include")
