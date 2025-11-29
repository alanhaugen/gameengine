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

add_custom_command(
    TARGET BallGame
    POST_BUILD # Executes after the target is built
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Assets" # Source directory
            "$<TARGET_FILE_DIR:BallGame>/Assets" # Destination directory
    COMMENT "Copying assets to BallGame's build directory"
)

add_custom_command(
    TARGET BallGame
    POST_BUILD # Executes after the target is built
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Shaders" # Source directory
            "$<TARGET_FILE_DIR:BallGame>/Shaders" # Destination directory
    COMMENT "Copying shaders to BallGame's build directory"
)

target_include_directories(BallGame PRIVATE "../../source")
target_include_directories(BallGame PRIVATE "../../include")
