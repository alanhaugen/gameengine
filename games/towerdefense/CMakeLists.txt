cmake_minimum_required(VERSION 3.19)
project(TowerDefense LANGUAGES CXX)

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
