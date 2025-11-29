cmake_minimum_required(VERSION 3.19)
project(BallGame LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Multimedia)

qt_standard_project_setup()

add_executable(BallGame
    CMakeLists.txt
    source/main.cpp
)

target_link_libraries(BallGame PRIVATE
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

target_include_directories(BallGame PRIVATE "../../source")
target_include_directories(BallGame PRIVATE "../../include")
