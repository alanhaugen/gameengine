cmake_minimum_required(VERSION 3.19)
project(QtVulkan LANGUAGES CXX)

find_package(Qt6 6.10.0 REQUIRED COMPONENTS Core Widgets Multimedia)

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
    shaders/color.frag
    shaders/color.vert
    shaders/gui.frag
    shaders/gui.vert
    source/x-platform/editor.h
    source/platforms/qt/qteditor.h source/platforms/qt/qteditor.cpp
    source/demos/empty.h source/demos/empty.cpp
    source/components/fpscamera.h source/components/fpscamera.cpp
    source/modules/ai/null/nullai.cpp source/modules/ai/null/nullai.h
    source/modules/filesystem/null/nullfilesystem.cpp source/modules/filesystem/null/nullfilesystem.h
    source/modules/physics/null/nullphysics.cpp source/modules/physics/null/nullphysics.h
    source/modules/renderer/null/nullrenderer.cpp source/modules/renderer/null/nullrenderer.h
    source/modules/script/null/nullscript.cpp source/modules/script/null/nullscript.h
    source/components/gameobject.h source/components/gameobject.cpp
    source/components/camera.h source/components/camera.cpp
    source/modules/audio/audio.h
    source/modules/ai/ai.h
    source/modules/filesystem/filesystem.h
    source/modules/physics/physics.h
    source/modules/audio/openal/openalaudio.h source/modules/audio/openal/openalaudio.cpp
    source/modules/audio/null/nullaudio.h source/modules/audio/null/nullaudio.cpp
    source/modules/system.h
    source/x-platform/locator.cpp
    source/x-platform/debug.h source/x-platform/debug.cpp
    source/demos/rollingball.cpp source/demos/rollingball.h
    source/components/terrain.cpp source/components/terrain.h
    source/components/trianglecollider.cpp source/components/trianglecollider.h
    source/components/spherecollider.cpp source/components/spherecollider.h
    source/x-platform/input.h
    source/x-platform/input.cpp
    source/modules/renderer/vulkan/vulkantexture.h
    source/modules/audio/openal/soundsource.h source/modules/audio/openal/soundsource.cpp
    source/modules/audio/openal/wavfilereader.h source/modules/audio/openal/wavfilereader.cpp
    source/modules/physics/aaphysics/aaphysics.h source/modules/physics/aaphysics/aaphysics.cpp
    source/components/sprite.h source/components/sprite.cpp
    source/demos/pong.h
    source/demos/pong.cpp
    source/components/cube.h source/components/cube.cpp
    source/components/text.h source/components/text.cpp
    source/components/sphere.h source/components/sphere.cpp
    source/modules/audio/qtaudio/qtmultimediaaudio.cpp source/modules/audio/qtaudio/qtmultimediaaudio.h
    source/demos/flappybird.cpp source/demos/flappybird.h
    source/demos/breakout.cpp source/demos/breakout.h
    source/towerdefense/game.cpp source/towerdefense/game.h source/towerdefense/gameover.cpp source/towerdefense/gameover.h source/towerdefense/mainmenu.cpp source/towerdefense/mainmenu.h source/towerdefense/victory.cpp source/towerdefense/victory.h
    source/demos/physicstestscene.h source/demos/physicstestscene.cpp
)
#OpenAL
if(DEFINED ENV{OPENAL_HOME})
    target_include_directories(QtVulkan PRIVATE $ENV{OPENAL_HOME}/include)

    target_link_libraries(QtVulkan PRIVATE $ENV{OPENAL_HOME}/libs/Win64/OpenAL32.lib)

    add_custom_command(TARGET QtVulkan POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $ENV{OPENAL_HOME}/bin/Win64/soft_oal.dll
            $<TARGET_FILE_DIR:QtVulkan>
    )
endif()

target_include_directories(QtVulkan PRIVATE include)

if(MSVC)
    # Required for proper C++ exception handling with MSVC
    target_compile_options(QtVulkan PRIVATE /EHsc)
    target_include_directories(QtVulkan PRIVATE
        "C:/VulkanSDK/1.4.321.1/Include"
    )
    target_link_libraries(QtVulkan PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::Widgets
        Qt6::Multimedia
        "C:/VulkanSDK/1.4.321.1/Lib/vulkan-1.lib"
    )
else()
    # This will set NDEBUG for both debug and release build
    # It stops Validation layers from being used - needs to be fixed!!!
    add_compile_definitions(NDEBUG)

    target_link_libraries(QtVulkan PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::Multimedia
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
install(TARGETS QtVulkan
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
