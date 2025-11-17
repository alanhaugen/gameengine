# GEA2025
Code for Game Engine Architecture 2025

[https://docs.google.com/document/d/1SOMO8CufboZFFjqsUNzGA5UfNpaCmmEuZl1iUjt-jw8/edit?tab=t.0#heading=h.h1nk9gnq12cz](https://docs.google.com/document/d/1SOMO8CufboZFFjqsUNzGA5UfNpaCmmEuZl1iUjt-jw8/edit?tab=t.0#heading=h.h1nk9gnq12cz)

[https://drive.google.com/drive/folders/1fOzgci2yONdo4kGF_0fjPAl83TqqWe1H](https://drive.google.com/drive/folders/1fOzgci2yONdo4kGF_0fjPAl83TqqWe1H)

## Coding conventions

Variables start with lowercase, camelCase

Methods/Functions and Classes/Structs start with uppercase, PascalCase.

All files should be in lowercase for cross platform support.

## Architecture

The engine is modular and has a core, consisting of components and platform specific code, and systems.

Applications made with the engine are found in games.

Here is a birdseye's view of the project:

* games
* source/core
* source/systems

The following systems are supported and can be swapped out:

* ai
* audio
* filesystem
* physics
* renderer
* script

There are already multiple implementations of some of the systems, and there are also null implementations of each system for disabling a system.

## Sources

The following font was used:

Noto Sans Japanese.

 License
Copyright 2014-2021 Adobe (http://www.adobe.com/), with Reserved Font Name 'Source'

This Font Software is licensed under the SIL Open Font License, Version 1.1 . This license is copied below, and is also available with a FAQ at: https://openfontlicense.org

SIL OPEN FONT LICENSE Version 1.1 - 26 February 2007 
