cmake_minimum_required(VERSION 3.19)
project(QtVulkan LANGUAGES CXX)

# Find Qt (Widgets implies Core)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Widgets Multimedia)

# Keep qt helper (optional but useful)
qt_standard_project_setup()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Qt's automoc/autouic/autorcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


# Detect build environment based on CMAKE_BINARY_DIR
# Used to set correct PATH and some clean up
if(${CMAKE_BINARY_DIR} MATCHES ".*out/.*")
    add_compile_definitions(BUILD_ENV_VISUAL_STUDIO)
    message(STATUS "=== Visual Studio detected ===")
elseif(${CMAKE_BINARY_DIR} MATCHES ".*build/.*")
    add_compile_definitions(BUILD_ENV_QTCREATOR)
    message(STATUS "=== Qt Creator detected ===")
    #Deleting preset files not used in Qt - generated in VS 2022
    #This should not fail even if the files are not present
    file(REMOVE "${CMAKE_CURRENT_SOURCE_DIR}/CMakePresets.json")
    file(REMOVE "${CMAKE_CURRENT_SOURCE_DIR}/CMakeUserPresets.json")
endif()


# Source files (include the .ui so AUTOUIC processes it)
set(SOURCES
    AssetManager/AssetManager.h AssetManager/AssetManager.cpp
    AssetManager/Mesh.h AssetManager/Mesh.cpp
    AssetManager/Sound.h AssetManager/Sound.cpp
    AssetManager/Texture.h AssetManager/Texture.cpp
    AssetManager/WavfileReader.h AssetManager/WavfileReader.cpp
    Core/Camera.h Core/Camera.cpp
    Core/Engine.h Core/Engine.cpp
    Core/Input.h
    Core/Renderer.h Core/Renderer.cpp
    Core/Utilities.h
    Core/Vertex.h
    ECS/Components.h
    ECS/Entity.h ECS/Entity.cpp
    ECS/RenderSystem.h ECS/RenderSystem.cpp
    ECS/ScriptingSystem.h ECS/ScriptingSystem.cpp
    ECS/SoundSystem.h ECS/SoundSystem.cpp
    ECS/Systems.h ECS/Systems.cpp
    Editor/DisplayWidget.cpp
    Editor/DraggableButton.h Editor/DraggableButton.cpp
    Editor/FilesWindow.h Editor/FilesWindow.cpp
    Editor/EntityContainer.h Editor/EntityContainer.cpp
    Editor/EntityModel.h Editor/EntityModel.cpp
    Editor/MainWindow.h Editor/MainWindow.cpp
    Editor/MainWindow.ui
    main.cpp
)

# all Lua files shown in IDE
file(GLOB LUA_FILES
    "Assets/Scripts/*.lua"
)

# all shader files shown in IDE
file(GLOB SHADER_FILES
    "Shaders/*.frag"
    "Shaders/*.vert"
)

add_executable(QtVulkan ${SOURCES} ${LUA_FILES} ${SHADER_FILES})

# MSVC-specific compile options (if building with MSVC)
if(MSVC)
    # Required for proper C++ exception handling with MSVC
    target_compile_options(QtVulkan PRIVATE /EHsc)
    # Include Vulkan headers (as requested)
    target_include_directories(QtVulkan PRIVATE
        $ENV{VULKAN_HOME}/Include
        $ENV{OPENAL_HOME}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/External/Lua/include
        ${CMAKE_CURRENT_SOURCE_DIR}
    )

    # Link the exact Vulkan library. Use the full path to the .lib
    # Also Link Qt libraries
    target_link_libraries(QtVulkan PRIVATE
        $ENV{VULKAN_HOME}/Lib/vulkan-1.lib
        $ENV{OPENAL_HOME}/libs/Win64/libOpenAL32.dll.a  # could be OpenAL32.lib
        ${CMAKE_CURRENT_SOURCE_DIR}/External/Lua/lib/lua5.4.3-static.lib
        Qt6::Widgets
        Qt6::Core
        Qt6::Multimedia
    )
elseif(APPLE)
    # This will set NDEBUG for both debug and release build
    # It stops Validation layers from being used - needs to be fixed!!!
    add_compile_definitions(NDEBUG)

    target_include_directories(QtVulkan PRIVATE
        #Hardcoded path for Oles Macs for now:
        "/Users/ole/VulkanSDK/1.4.321.0/macOS/include"
    )
    target_link_libraries(QtVulkan PRIVATE
        Qt::Core
        Qt::Widgets
        "-framework QuartzCore"
        "-framework Metal"
        "-framework Foundation"
        "-framework IOSurface"
        "-framework CoreGraphics"
        "-framework IOKit"
        "-framework AppKit"
        #Hardcoded path for Oles Macs for now:
        "/Users/ole/VulkanSDK/1.4.321.0/macOS/lib/MoltenVK.xcframework/macos-arm64_x86_64/libMoltenVK.a"
    )
target_link_libraries(QtVulkan PRIVATE Qt6::Widgets)
endif()


# Copy the DLL after build
# This makes the .exe use the correct .dll from the library we compile to
# (the "COMMAND echo" only works on Windows)
add_custom_command(TARGET QtVulkan POST_BUILD
    COMMAND echo Copying OpenAL32.dll...
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $ENV{OPENAL_HOME}/bin/Win64/OpenAL32.dll           #Windows environment variable version
        $<TARGET_FILE_DIR:QtVulkan>
    )
