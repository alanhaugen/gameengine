cmake_minimum_required(VERSION 3.19)
project(Core LANGUAGES CXX)

#############################################################
##
## Project configuration
## You can set modules here
##
## If you do not set anything, these are set automatically
##
#############################################################

set(RENDERER VulkanRenderer)
#set(RENDERER OpenGLRenderer)
#set(RENDERER NullRenderer)
if(DEFINED ENV{OPENAL_HOME})
    set(AUDIO OpenALAudio)
else()
    #set(AUDIO NullAudio)
    set(AUDIO QtMultimediaAudio)
endif()
#set(SCRIPT LuaScript)
set(SCRIPT NullScript)
#set(FILESYSTEM STDFilesystem)
set(FILESYSTEM NullFilesystem)
set(PHYSICS AAPhysics)
#set(PHYSICS Bullet3Physics)
#set(PHYSICS NullPhysics)

add_compile_definitions(RENDERER=${RENDERER})
add_compile_definitions(AUDIO=${AUDIO})
add_compile_definitions(SCRIPT=${SCRIPT})
add_compile_definitions(FILESYSTEM=${FILESYSTEM})
add_compile_definitions(PHYSICS=${PHYSICS})
add_compile_definitions(AUDIO=${AUDIO})
add_compile_definitions(AI=${AI})

#############################################################
##
##  You do not need to change any code beyond this point
##
#############################################################

# Asset Conditioning Pipeline (ACP)

#############################################################

add_subdirectory(source/systems/ai/null)
add_subdirectory(source/systems/audio/null)
add_subdirectory(source/systems/script/null)
add_subdirectory(source/systems/renderer/null)
add_subdirectory(source/systems/physics/null)
add_subdirectory(source/systems/filesystem/null)

add_subdirectory(source/systems/audio/qtaudio)
add_subdirectory(source/systems/physics/aaphysics)
add_subdirectory(source/systems/renderer/vulkan)
add_subdirectory(source/systems/renderer/opengl)

add_subdirectory(games/demos)
add_subdirectory(games/rpg)
add_subdirectory(games/towerdefense)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Multimedia)

qt_standard_project_setup()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Core STATIC
    README.md
    shaders/color.vert
    shaders/color.frag
    shaders/gui.vert
    shaders/gui.frag
    shaders/phong.vert
    shaders/phong.frag
    shaders/Shader.vert
    shaders/Shader.frag
    shaders/skinning.vert
    shaders/skinning.frag
    source/core/components/camera.cpp
    source/core/components/camera.h
    source/core/components/component.h
    source/core/components/cube.cpp
    source/core/components/cube.h
    source/core/components/fpscamera.cpp
    source/core/components/fpscamera.h
    source/core/components/gameobject.cpp
    source/core/components/gameobject.h
    source/core/components/gameobject.cpp
    source/core/components/gameobject.h
    source/core/components/mesh.cpp
    source/core/components/mesh.h
    source/core/components/sphere.cpp
    source/core/components/sphere.h
    source/core/components/spherecollider.cpp
    source/core/components/spherecollider.h
    source/core/components/sprite.cpp
    source/core/components/sprite.h
    source/core/components/terrain.cpp
    source/core/components/terrain.h
    source/core/components/text.cpp
    source/core/components/text.h
    source/core/components/trianglecollider.cpp
    source/core/components/trianglecollider.h
    source/core/components/visualobject.h
    source/core/platforms/application.cpp
    source/core/platforms/application.h
    source/core/platforms/qt/mainwindow.cpp
    source/core/platforms/qt/mainwindow.h
    source/core/platforms/qt/MainWindow.ui
    source/core/platforms/qt/qtapplication.cpp
    source/core/platforms/qt/qtapplication.h
    source/core/platforms/qt/qteditor.cpp
    source/core/platforms/qt/qteditor.h
    source/core/x-platform/debug.cpp
    source/core/x-platform/debug.h
    source/core/x-platform/editor.h
    source/core/x-platform/input.cpp
    source/core/x-platform/input.h
    source/core/x-platform/locator.cpp
    source/core/x-platform/locator.h
    source/core/x-platform/scene.h
    source/core/components/AssetManager.h
    source/core/components/AssetManager.cpp
    source/core/x-platform/services.h source/core/x-platform/services.cpp)

target_include_directories(Core PRIVATE "source")

#OpenAL
if(AUDIO STREQUAL "OpenALAudio")
    #message("Will try to use " AUDIO)
if(DEFINED ENV{OPENAL_HOME})
    set(AUDIO OpenALAudio)

    add_subdirectory(source/systems/audio/openal)
    target_include_directories(Core PRIVATE $ENV{OPENAL_HOME}/include)

    target_link_libraries(Core PRIVATE OpenALAudio)

    add_custom_command(TARGET Core POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $ENV{OPENAL_HOME}/bin/Win64/OpenAL32.dll
            $<TARGET_FILE_DIR:Core>
    )
else()

endif()
endif()

target_include_directories(Core PRIVATE include)

if (WIN32)
    if (MSVC)
        # Required for proper C++ exception handling with MSVC
        target_compile_options(Core PRIVATE /EHsc)
    endif()

    target_include_directories(Core PRIVATE
        $ENV{VULKAN_SDK}/Include
    )
    target_link_libraries(Core PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Multimedia
        $ENV{VULKAN_SDK}/Lib/vulkan-1.lib
    )
else()
    # This will set NDEBUG for both debug and release build
    # It stops Validation layers from being used - needs to be fixed!!!
    add_compile_definitions(NDEBUG)

    target_link_libraries(Core PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Multimedia
        "-framework QuartzCore"
        "-framework Metal"
        "-framework Foundation"
        "-framework IOSurface"
        "-framework CoreGraphics"
        "-framework IOKit"
        "-framework AppKit"
        #Hardcoded path for Oles Macs for now:
        #"/Users/ole/VulkanSDK/1.4.321.0/macOS/lib/MoltenVK.xcframework/macos-arm64_x86_64/libMoltenVK.a"
        ${CMAKE_SOURCE_DIR}/lib/darwin/arm64/libMoltenVK.a
    )
endif()

#file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Shaders" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
#file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

include(GNUInstallDirs)
install(TARGETS Core
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
