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

add_custom_command(
    TARGET RPG
    POST_BUILD # Executes after the target is built
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Assets" # Source directory
            "$<TARGET_FILE_DIR:RPG>/Assets" # Destination directory
    COMMENT "Copying assets to RPG's build directory"
)

add_custom_command(
    TARGET RPG
    POST_BUILD # Executes after the target is built
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Shaders" # Source directory
            "$<TARGET_FILE_DIR:RPG>/Shaders" # Destination directory
    COMMENT "Copying shaders to RPG's build directory"
)

target_include_directories(RPG PRIVATE "../../source")
target_include_directories(RPG PRIVATE "../../include")
