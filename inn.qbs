Application {
    cpp.cxxLanguageVersion: "c++23"
    name: "Game"

    files: [
        "source/renderer.cpp",
        "source/renderer.h",
        "source/mainwindow.h",
        "source/mainwindow.cpp",
        "source/utilities.h",
        "source/vertex.h",
        "source/main.cpp",
        "CMakeLists.txt",
        "source/MainWindow.ui",
        "Shaders/Shader.vert",
        "Shaders/Shader.frag",
    ]

    Depends { name: "cpp" }

    Depends {
        name: "Qt";
        submodules: ["core", "gui", "widgets"]
    }

    cpp.includePaths: "include"
    cpp.staticLibraries: "MoltenVK"

    property stringList macosFrameworks: [
        "CoreMIDI",
        "CoreFoundation",
        "AudioToolbox",
        "CoreAudio",
        "Carbon",
        "ForceFeedback",
        "CoreVideo",
        "AppKit",
        "OpenGL",
        "Metal",
        "IOKit",
        "Cocoa",
    ]

    cpp.frameworks: {
        if (qbs.architecture.includes("arm64"))
            return macosFrameworks.concat(
                        "CoreHaptics",
                        "MediaPlayer",
                        "GameController",
                        "QuartzCore",
                        "IOSurface")
        return macosFrameworks
    }

    cpp.libraryPaths: [project.buildDirectory, "lib/darwin/" + qbs.architecture]

    /*Properties {
        condition: qbs.targetOS.contains("macos")

        cpp.frameworks: {
            if (qbs.architecture.includes("arm64"))
                return macosFrameworks.concat(
                            "CoreHaptics",
                            "MediaPlayer",
                            "GameController",
                            "QuartzCore",
                            "IOSurface")
            return macosFrameworks
        }

        cpp.dynamicLibraries: macosSharedLibs

        cpp.staticLibraries: staticLibs.concat("SDL2", "MoltenVK")

        cpp.libraryPaths: [project.buildDirectory, "../solid/lib/debug/darwin/" + qbs.architecture]
        cpp.includePaths: includePaths.concat("../solid/include/darwin")
        cpp.defines: project.defines.concat(project.sdlDefines)
    }

    Properties {
        condition: qbs.targetOS.contains("linux")

        //cpp.dynamicLibraries: linuxSharedLibs
        cpp.staticLibraries: staticLibs.concat("SDL2")

        cpp.libraryPaths: [project.buildDirectory, "../solid/lib/debug/linux/" + qbs.architecture]
        cpp.includePaths: includePaths.concat("../solid/include/linux")
        cpp.defines: project.defines.concat(project.sdlDefines)
    }

    Properties {
        condition: qbs.targetOS.contains("windows")

        cpp.dynamicLibraries: windowsSharedLibs
        cpp.staticLibraries: staticLibs

        cpp.libraryPaths: [project.buildDirectory, "../solid/lib/debug/mingw32/x86_64"]
        cpp.includePaths: includePaths.concat("../solid/include/mingw32")
        cpp.defines: project.defines.concat(project.windowsDefines)
    }*/
}
