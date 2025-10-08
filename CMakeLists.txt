cmake_minimum_required(VERSION 3.19)
project(QtVulkan LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
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
    main.cpp
    Renderer.cpp
    Renderer.h
    Utilities.h
    Vertex.h
    MainWindow.cpp
    MainWindow.h
    MainWindow.ui
    assetmanager.h assetmanager.cpp
    fileswindow.h fileswindow.cpp
    displayWidget.cpp
    draggablebutton.h draggablebutton.cpp
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

