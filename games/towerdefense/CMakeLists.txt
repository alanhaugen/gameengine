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
    source/splash.h source/splash.cpp
    source/physicstest.h source/physicstest.cpp

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

add_custom_command(
    TARGET TowerDefense
    POST_BUILD # Executes after the target is built
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Assets" # Source directory
            "$<TARGET_FILE_DIR:TowerDefense>/Assets" # Destination directory
    COMMENT "Copying assets to TowerDefense's build directory"
)

add_custom_command(
    TARGET TowerDefense
    POST_BUILD # Executes after the target is built
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Shaders" # Source directory
            "$<TARGET_FILE_DIR:TowerDefense>/Shaders" # Destination directory
    COMMENT "Copying shaders to TowerDefense's build directory"
)

target_include_directories(TowerDefense PRIVATE "../../source")
target_include_directories(TowerDefense PRIVATE "../../include")
