cmake_minimum_required(VERSION 3.19)
project(Demos LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Multimedia)

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
    TARGET Demos
    POST_BUILD # Executes after the target is built
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Assets" # Source directory
            "$<TARGET_FILE_DIR:Demos>/Assets" # Destination directory
    COMMENT "Copying assets to Demos's build directory"
)

add_custom_command(
    TARGET Demos
    POST_BUILD # Executes after the target is built
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Shaders" # Source directory
            "$<TARGET_FILE_DIR:Demos>/Shaders" # Destination directory
    COMMENT "Copying shaders to Demos's build directory"
)

target_include_directories(Demos PRIVATE "../../source")
target_include_directories(Demos PRIVATE "../../include")
