set(Qt6_DIR C:\Qt\6.9.3\msvc2022_64\lib\cmake\Qt6)
cmake_minimum_required(VERSION 3.19)
project(QtVulkan LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Widgets Multimedia)
find_package(Vulkan REQUIRED )

qt_standard_project_setup()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Adding External library:
# ----------------
# Using Windows environment variable:
# Add include directory


# Enable Qt's automoc/autouic/autorcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find Qt (Widgets implies Core)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Keep qt helper (optional but useful)
qt_standard_project_setup()

# Source files (include the .ui so AUTOUIC processes it)
set(SOURCES
    AssetManager.h AssetManager.cpp
    Components.h
    DisplayWidget.cpp
    DraggableButton.h DraggableButton.cpp
    Engine.h Engine.cpp
    Entity.h Entity.cpp
    FilesWindow.h FilesWindow.cpp
    main.cpp
    MainWindow.h MainWindow.cpp
    MainWindow.ui
    Mesh.h Mesh.cpp
    Renderer.h Renderer.cpp
    RenderSystem.h RenderSystem.cpp
    System.h
    Texture.h Texture.cpp
    Utilities.h
    Vertex.h

    Shaders/Shader.frag
    Shaders/Shader.vert
    Shaders/Phong.frag
    Shaders/Phong.vert
    SoundComponent.h
    resource.qrc
    Sound.cpp
    Sound.h
)

add_executable(QtVulkan ${SOURCES})


# MSVC-specific compile options (if building with MSVC)
if (MSVC)
    target_compile_options(QtVulkan PRIVATE /EHsc)
    # Include Vulkan headers (as requested)
    target_include_directories(QtVulkan PRIVATE
        $ENV{VULKAN_HOME}/Include
    )

    # Link the exact Vulkan library. Use the full path to the .lib
    # Also Link Qt libraries
    target_link_libraries(QtVulkan PRIVATE
        $ENV{VULKAN_HOME}/Lib/vulkan-1.lib
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

