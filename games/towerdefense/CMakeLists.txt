cmake_minimum_required(VERSION 3.19)
project(TowerDefense LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Multimedia)

qt_standard_project_setup()

add_executable(TowerDefense
    CMakeLists.txt
    source/main.cpp
    source/game.cpp
    source/game.h
    source/gameover.cpp
    source/gameover.h
    source/mainmenu.cpp
    source/mainmenu.h
    source/victory.cpp
    source/victory.h
)

target_link_libraries(TowerDefense PRIVATE
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

target_include_directories(TowerDefense PRIVATE "../../source")
target_include_directories(TowerDefense PRIVATE "../../include")
