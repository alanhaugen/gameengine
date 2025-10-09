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

# Source files (include the .ui so AUTOUIC processes it)
set(SOURCES
    AssetManager.h AssetManager.cpp
    Camera.h Camera.cpp
    Components.h
    DisplayWidget.cpp
    DraggableButton.h DraggableButton.cpp
    Engine.h Engine.cpp
    Entity.h Entity.cpp
    EntityContainer.h EntityContainer.cpp
    EntityModel.h EntityModel.cpp
    FilesWindow.h FilesWindow.cpp
    Input.h
    main.cpp
    MainWindow.h MainWindow.cpp
    MainWindow.ui
    Mesh.h Mesh.cpp
    Renderer.h Renderer.cpp
    RenderSystem.h RenderSystem.cpp
    Sound.h Sound.cpp
    System.h
    Systems.h Systems.cpp
    Texture.h Texture.cpp
    Utilities.h
    Vertex.h
    WavfileReader.h WavfileReader.cpp

    Shaders/Shader.frag
    Shaders/Shader.vert
    Shaders/Phong.frag
    Shaders/Phong.vert
)

add_executable(QtVulkan ${SOURCES})

# MSVC-specific compile options (if building with MSVC)
if(MSVC)
    # Required for proper C++ exception handling with MSVC
    target_compile_options(QtVulkan PRIVATE /EHsc)
    # Include Vulkan headers (as requested)
    target_include_directories(QtVulkan PRIVATE
        $ENV{VULKAN_HOME}/Include
        $ENV{OPENAL_HOME}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/External/Lua/include
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
