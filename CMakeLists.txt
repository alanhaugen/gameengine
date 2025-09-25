cmake_minimum_required(VERSION 3.19)
project(QtVulkan LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(QtVulkan
    source/modules/renderer/vulkan/vulkanrenderer.cpp
    source/modules/renderer/vulkan/vulkanrenderer.h
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
    source/x-platform/scene.h
    source/x-platform/locator.h
    source/demos/vikingscene.cpp
    source/demos/vikingscene.h
    source/components/component.h
    source/components/mesh.cpp
    source/components/mesh.h
    source/modules/renderer/renderer.h
    shaders/phong.frag
    shaders/phong.vert
    shaders/shader.frag
    shaders/shader.vert
    source/x-platform/editor.h
    source/platforms/qt/qteditor.h source/platforms/qt/qteditor.cpp
    source/demos/empty.h source/demos/empty.cpp
    source/components/fpscamera.h source/components/fpscamera.cpp
    source/modules/ai/null/nullai.cpp source/modules/ai/null/nullai.h
    source/modules/filesystem/null/nullfilesystem.cpp source/modules/filesystem/null/nullfilesystem.h
    source/modules/physics/null/nullphysics.cpp source/modules/physics/null/nullphysics.h
    source/modules/renderer/null/nullrenderer.cpp source/modules/renderer/null/nullrenderer.h
    source/modules/script/null/nullscript.cpp source/modules/script/null/nullscript.h

)

#OpenAL
if(DEFINED ENV{OPENAL_HOME})


    target_include_directories(QtVulkan PRIVATE $ENV{OPENAL_HOME}/include)

    target_link_libraries(QtVulkan PRIVATE $ENV{OPENAL_HOME}/libs/Win64/OpenAL32.lib)

    add_custom_command(TARGET QtVulkan POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $ENV{OPENAL_HOME}/bin/Win64/OpenAL32.dll
            $<TARGET_FILE_DIR:QtVulkan>
    )
endif()

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

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Shaders" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

include(GNUInstallDirs)
install(TARGETS QtVulkan
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
