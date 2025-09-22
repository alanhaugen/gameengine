cmake_minimum_required(VERSION 3.19)
project(QtVulkan LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(QtVulkan
    source/main.cpp
    source/renderer.h source/renderer.cpp
    source/utilities.h
    source/vertex.h
    source/mainwindow.h source/mainwindow.cpp
    source/mainwindow.ui
)

if(MSVC)
    # Required for proper C++ exception handling with MSVC
    target_compile_options(QtVulkan PRIVATE /EHsc)
    target_include_directories(QtVulkan PRIVATE
    "C:/VulkanSDK/1.4.321.1/Include"
    )
    target_link_libraries(QtVulkan PRIVATE
    Qt::Core
    Qt::Widgets
    "C:/VulkanSDK/1.4.321.1/Lib/vulkan-1.lib"
    )
target_link_libraries(QtVulkan PRIVATE Qt6::Widgets)
endif()

include(GNUInstallDirs)
install(TARGETS QtVulkan
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
