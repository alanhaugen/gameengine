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
    Shaders/Shader.frag
    Shaders/Shader.vert
    Shaders/Phong.frag
    Shaders/Phong.vert
    Mesh.h Mesh.cpp
    RenderComponent.h RenderComponent.cpp
    Texture.cpp Texture.h
    TransformComponent.cpp TransformComponent.h
    Components.h
    Entity.cpp
    Entity.h
    System.h
    TransformComponent.cpp TransformComponent.h
    RenderSystem.cpp RenderSystem.h
)

add_executable(QtVulkan ${SOURCES}
    Components.h Entity.h)


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
else()
    # This will set NDEBUG for both debug and release build
    # It stops Validation layers from being used - needs to be fixed!!!
    add_compile_definitions(NDEBUG)

    target_include_directories(QtVulkan PRIVATE
        #Hardcoded path for Oles Macs for now:
        "/Users/awh/VulkanSDK/1.4.304.1/macOS/include"
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
        "/Users/awh/inn/GEA2025/lib/darwin/arm64/libMoltenVK.a"
    )
target_link_libraries(QtVulkan PRIVATE Qt6::Widgets)
endif()


# Install rules (optional)
include(GNUInstallDirs)
install(TARGETS QtVulkan
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
