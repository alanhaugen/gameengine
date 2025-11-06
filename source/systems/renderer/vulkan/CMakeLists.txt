cmake_minimum_required(VERSION 3.19)
project(VulkanRenderer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

add_library(VulkanRenderer STATIC
    CMakeLists.txt
    ../renderer.h
    utilities.h
    vulkantexture.h
    vulkanrenderer.h
    vulkanrenderer.cpp
)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

target_link_libraries(VulkanRenderer PRIVATE
    Qt::Widgets
)

target_include_directories(VulkanRenderer PRIVATE ../../../../include)
target_include_directories(VulkanRenderer PRIVATE ../../../../source)
