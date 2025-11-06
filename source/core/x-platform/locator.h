#pragma once

#include "input.h"
#include "debug.h"
#include "editor.h"
#include "systems/audio/null/nullaudio.h"
#include "systems/filesystem/null/nullfilesystem.h"
#include "systems/physics/null/nullphysics.h"
#include "systems/renderer/null/nullrenderer.h"
#include "systems/script/null/nullscript.h"

#include <vector>
#include <string>
#include "systems/system.h"

class Locator
{
public:
    static void SetEditor(Editor *_editor);
    static void SetDebug(Debug *_debug);
    static void SetAudio(Audio *_audio);
    static void SetFileSystem(FileSystem *_fileSystem);
    static void SetPhysics(Physics *_physics);
    static void SetRenderer(Renderer *_renderer);
    static void SetScript(Script *_script);

    static Debug* debug;
    static Audio* audio;
    static FileSystem* filesystem;
    static Physics* physics;
    static Renderer* renderer;
    static Script* script;
    static Editor* editor;
    static Input input;

private:
    static NullAudio nullAudio;
    static NullFileSystem nullFileSystem;
    static NullPhysics nullPhysics;
    static NullRenderer nullRenderer;
    static NullScript nullScript;
};

//! Macro to easily access the debug singleton and Log a message
#define Log(string) if(Locator::debug) Locator::debug->Write(string)

//! Macro to easily access the debug singleton and Log a warning
#define LogWarning(string) if(Locator::debug) Locator::debug->Warning(std::string(__FILE__) + std::string("(") + std::string(__LINE__) + std::string("): ") + std::string(string) )

//! Macro to easily access the debug singleton and Log an error
#define LogError(string) if(Locator::debug) Locator::debug->Error(string) //(std::string("Error ") + std::string(__FILE__) + "(" + std::string(__LINE__) + "): " + string )
