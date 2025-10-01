cmake_minimum_required(VERSION 3.19)
project(QtVulkan LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
    Components.h
    Entity.cpp
    Entity.h
    System.h
)

add_executable(QtVulkan ${SOURCES}
    Components.h Entity.h
    EntityModel.h EntityModel.cpp
    EntityContainer.h EntityContainer.cpp)


# MSVC-specific compile options (if building with MSVC)
if (MSVC)
    target_compile_options(QtVulkan PRIVATE /EHsc)
    # Include Vulkan headers (as requested)
    target_include_directories(QtVulkan PRIVATE
        "C:/VulkanSDK/1.4.321.1/Include"
    )

    # Link the exact Vulkan library you specified
    # (Use the full path to the .lib that you requested.)
    # Also Link Qt libraries
    target_link_libraries(QtVulkan PRIVATE
        "C:/VulkanSDK/1.4.321.1/Lib/vulkan-1.lib"
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
endif()


# Install rules (optional)
include(GNUInstallDirs)
install(TARGETS QtVulkan
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
