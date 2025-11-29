/*! \mainpage Hulgra Games inngine Index Page
 *
 * version 1, 2025
 *
 * This doc is written for Universirt of innlandet as part of the GEA2025 Game Engine course
 *
 * \section source Getting the source
 *
 * git is required, see Installing dependencies
 *
 *  > git clone ssh://git@github.com:INN-DGE/GEA2025.git
 *
 * \subsection dependencies_Windows Windows
 *
 * Install Git https://git-scm.com/download/win
 *
 * Install Vulkan SDK https://vulkan.lunarg.com/
 *
 * Install QtCreator Open-Source edition https://www.qt.io/download-open-source
 *
 * *Tip: During installation, click Select Qt libraries and tools*
 *
 * Open the QtCreator project CMakelists.txt
 *
 * \subsection build_configuration Configuration
 *
 * Systems will be automatically set depending on your configuration.
 *
 * If you have OPENAL_HOME environment variable set, you will automatically use OpenALAudio.
 *
 * Otherwise, QtMultiMediaAudio is chosen. There is support for NullAudio too, but it must be set manually.
 *
 * Every system has a null version.
 *
 * Here are all the supported systems.
 *
 * VARIABLE                                       | DESCRIPTION
 * ------------                                   | -------------
 * PLATFORM=[QtApplication\|GLFWApplication]      | Set build platform
 * AUDIO=[QtMultimediaAudio\|OpenALAudio]         | Sets audio renderer
 * RENDERER=[VulkanRenderer\|OpenGLRenderer]      | Sets graphics renderer
 * PHYSICS=[AAPhysics]                            | Sets body dynamics system
 * SCRIPT=[LuaScript\|AngelScript]                | Sets scripting system
 * FILESYSTEM=[StdFileSystem]                     | Sets filesystem abstraction
 *
 * \subsection environment_vars Environment Variables
 *
 * You may define environment variables which will change default build behaviour,
 * which in turn changes the default configuration. See build_configuration for details.
 *
 * You could set these in QtCreator: Projects -> Build -> Build Environment (remember to set your configuration for both your executable project and core project)
 *
 * \section structure_sec Structure
 *
 * DIRECTORY              | CONTENTS
 * ------------           | -------------
 * source/core            | consists of x-platform and platform
 * source/core/x-platform | describes generic interconnected functions universal to all platforms
 * source/core/platform   | specifies platform specific code
 * source/core/components | standard components which can be added to game objects
 * source/systems         | consists of ai, audio, filesystem, physics, renderer and script systems
 * include                | consists of 3rdparty libraries used to build the framework
 * games                  | video-games made with the game engine
 *
 * \subsection structure_platform Platform
 *
 * Application is the main object for a game made with this enigne, found in application.h
 *
 * PLATFORM inherits Locator which has the following objects:
 *  * debug
 *  * ai
 *  * audio
 *  * renderer
 *  * physics
 *  * filesystem
 *  * script
 *
 * \subsection structure Input
 *
 * Input consists of three layers
 *
 *  * Raw input gathering
 *  * Input mapping
 *  * High level handler
 *
 * The two first layers are platform specific, hence, their implementation should be done when implementing
 * a new application platform.
 *
 * input.OnButton(const unsigned int button, bool isDown) is called to pass raw input into the input handler.
 *
 * input.Define(const char *controlName, const unsigned int key, ...) is used for keymapping
 *
 * The data structure Input functions as the high-level handler, and can be used by an application to process
 * input. Example: if (input.Held(input.Key.C)) { ... }
 *
 * \subsection structure_components Components
 *
 * Components implement functionality, such as Sprite, Mesh, Text, FPVCamera, Camera, RigidBody,
 * Terrain, TerrainSnap, Timer, TrackingSpline, WiredCube, Cube, Sphere, BoxCollider, SphereCollider,
 * BallEmitter, SnowGlobeCamera, BSplineSurface, TriangleCollider, custom game mechanics, etc.
 *
 * Components are automatically updated each from when they are attached to a game object.
 *
 * \section profiling Profiling
 *
 * You could use RenderDoc (https://renderdoc.org/) for profiling of OpenGL and Vulkan renderers.
 *
 * \section documentation_sec Documentation
 *
 * Download doxygen
 *
 * If you want your code descriptions to appear in the docs, use //!, they may span several lines
 *
 * To generate the documentation, you need doxygen:
 *  > cd docs
 *
 *  > doxygen
 *
 * \section conventions_sec Coding Conventions
 *
 * Look at the following in application.h, which is where the doxygen main page is (you will need to open it in an editor)
 *
 * <code>
 * #include "core/application.h" \n
 * \n
 * const int constantInteger; \n
 *
 * class ClassName \n
 * { \n
 * private: \n
 *     int memberVariable; \n
 * \n
 * public: \n
 *     ClassName(); \n
 *     inline void MethodName() { int localVariable = 1; } \n
 * }; \n
 * \n
 * void SomeFunction() \n
 * { \n
 *     // four spaces instead of tab \n
 * } \n
 * </code>
 *
 * Expand tabs to four spaces
 *
 * Don't use stdio or iostream unless it has been sanitized by #ifndef NDEBUG\\ printf \\#endif
 *
 * Never use third party libraries which break the previous rule
 *
 * Inside the application, always write full paths to includes, do not use .. etc. For example DO: "core/x-platform/locator.h" DON'T: "../renderer.h"
 *
 * You may #include "core/application.h" and use the Log(""), LogError("") and LogWarning("") macros
 *
 * \section third_party Third Party Licenses
 *
 * The following font was used:
 *
 * Noto Sans Japanese.
 *
 * License
 * Copyright 2014-2021 Adobe (http://www.adobe.com/), with Reserved Font Name 'Source'
 *
 * This Font Software is licensed under the SIL Open Font License, Version 1.1 . This license is copied below, and is also available with a FAQ at: https://openfontlicense.org
 *
 * SIL OPEN FONT LICENSE Version 1.1 - 26 February 2007
 *
 */

#pragma once

#define PLATFORM_HEADER "qt/qtapplication.h"
#define PLATFORM QtApplication

#include PLATFORM_HEADER

class Application : public PLATFORM
{
public:
    Application(int argc, char* argv[], const char* windowTitle, int windowWidth, int windowHeight);
    void SetScene(int scene);
    static void NextScene();
    static void Quit();
    int Run();
};
