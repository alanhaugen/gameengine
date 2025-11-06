cmake_minimum_required(VERSION 3.19)
project(Demos LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

add_executable(Demos
    CMakeLists.txt
    source/main.cpp
    source/breakout.cpp
    source/breakout.h
    source/empty.cpp
    source/empty.h
    source/flappybird.cpp
    source/flappybird.h
    source/pong.cpp
    source/pong.h
    source/rollingball.cpp
    source/rollingball.h
    source/vikingscene.cpp
    source/vikingscene.h
)

target_link_libraries(Demos PRIVATE
    Core # The inn game engine
    Qt::Widgets

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

target_include_directories(Demos PRIVATE "../../source")
target_include_directories(Demos PRIVATE "../../include")
