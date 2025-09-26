#include "locator.h"

Debug *Locator::debug = NULL;
Editor *Locator::editor = NULL;

NullAudio Locator::nullAudio;
NullFileSystem Locator::nullFileSystem;
NullPhysics Locator::nullPhysics;
NullRenderer Locator::nullRenderer;
NullScript Locator::nullScript;

Audio *Locator::audio = &Locator::nullAudio;
FileSystem *Locator::filesystem = &Locator::nullFileSystem;
Physics *Locator::physics = &Locator::nullPhysics;
Renderer *Locator::renderer = &Locator::nullRenderer;
Script *Locator::script = &Locator::nullScript;

void Locator::SetEditor(Editor *_editor)
{
    if (_editor == NULL)
    {
        editor = NULL;
    }
    else
    {
        editor = _editor;
    }
}

void Locator::SetDebug(Debug *_debug)
{
    if (_debug == NULL)
    {
        debug = NULL;
    }
    else
    {
        debug = _debug;
    }
}

void Locator::SetAudio(Audio *_audio)
{
    if (_audio == NULL)
    {
        // Revert to null system
        audio = &nullAudio;
    }
    else
    {
        audio = _audio;
    }
}

void Locator::SetFileSystem(FileSystem *_fileSystem)
{
    if (_fileSystem == NULL)
    {
        // Revert to null system
        filesystem = &nullFileSystem;
    }
    else
    {
        filesystem = _fileSystem;
    }
}

void Locator::SetPhysics(Physics *_physics)
{
    if (_physics == NULL)
    {
        // Revert to null system
        physics = &nullPhysics;
    }
    else
    {
        physics = _physics;
    }
}

void Locator::SetRenderer(Renderer *_renderer)
{
    if (_renderer == NULL)
    {
        // Revert to null system
        renderer = &nullRenderer;
    }
    else
    {
        renderer = _renderer;
    }
}

void Locator::SetScript(Script *_script)
{
    if (_script == NULL)
    {
        // Revert to null system
        script = &nullScript;
    }
    else
    {
        script = _script;
    }
}
