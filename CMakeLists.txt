cmake_minimum_required(VERSION 3.19)
project(QtVulkan LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(QtVulkan
    source/modules/renderer/vulkan/renderer.cpp
    source/modules/renderer/vulkan/renderer.h
    source/platforms/qt/mainwindow.h
    source/platforms/qt/mainwindow.cpp
    source/modules/renderer/vulkan/utilities.h
    source/modules/renderer/vertex.h
    source/main.cpp
    CMakeLists.txt
    source/platforms/application.cpp
    source/platforms/application.h
    source/platforms/qt/MainWindow.ui
    source/platforms/qt/qtapplication.cpp
    source/platforms/qt/qtapplication.h
)

include_directories(${CMAKE_SOURCE_DIR}/include)

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
else()
    find_library(COREAUDIO CoreAudio "/usr")
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
    ${CMAKE_SOURCE_DIR}/lib/darwin/arm64/libMoltenVK.a
    )
endif()

include(GNUInstallDirs)
install(TARGETS QtVulkan
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
