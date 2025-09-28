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
    Entity.h
    Components.h
)

add_executable(QtVulkan ${SOURCES}
    Components.h Entity.h)

# Include Vulkan headers (as requested)
target_include_directories(QtVulkan PRIVATE
    "C:/VulkanSDK/vulkan/Include"
)

# Link Qt libraries
target_link_libraries(QtVulkan PRIVATE
    Qt6::Widgets
    Qt6::Core
)

# Link the exact Vulkan library you specified
# (Use the full path to the .lib that you requested.)
target_link_libraries(QtVulkan PRIVATE
    "C:/VulkanSDK/vulkan/Lib/vulkan-1.lib"
)

# MSVC-specific compile options (if building with MSVC)
if (MSVC)
    target_compile_options(QtVulkan PRIVATE /EHsc)
endif()

# Install rules (optional)
include(GNUInstallDirs)
install(TARGETS QtVulkan
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
