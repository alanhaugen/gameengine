#pragma once

class GLFWApplication
{
private:

protected:
    Scene* currentScene = nullptr;
    Editor* editor;

public:
    GLFWApplication(int argc, char* argv[], const char* windowTitle, int windowWidth, int windowHeight);
    static void NextScene();
    static void Quit();
    int Run();
};

