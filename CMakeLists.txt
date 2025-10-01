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


add_executable(QtVulkan
    main.cpp
    Renderer.h Renderer.cpp
    Utilities.h
    Vertex.h
    MainWindow.h MainWindow.cpp
    MainWindow.ui
    assetmanager.h assetmanager.cpp
    fileswindow.h fileswindow.cpp
    displayWidget.cpp
)

if(MSVC)
    # Required for proper C++ exception handling with MSVC
    target_compile_options(QtVulkan PRIVATE /EHsc)
    #target_include_directories(QtVulkan PRIVATE
    #$ENV{VULKAN_HOME}/include
    #)
    target_link_libraries(QtVulkan PRIVATE
    Qt::Core
    Qt::Widgets
    Vulkan::Vulkan
    #$ENV{VULKAN_HOME}/include
    )
target_link_libraries(QtVulkan PRIVATE Qt6::Widgets)
endif()

include(GNUInstallDirs)
install(TARGETS QtVulkan
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
