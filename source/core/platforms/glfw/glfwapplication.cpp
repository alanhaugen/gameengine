#include "glfwapplication.h"
#include "core/x-platform/locator.h"

GLFWApplication::GLFWApplication(int argc, char* argv[], const char* windowTitle, int windowWidth, int windowHeight)
{
}

void GLFWApplication::NextScene()
{
    LogWarning("GLFW platform does not support moving to next scene");
}

void GLFWApplication::Quit()
{
}

int GLFWApplication::Run()
{
}
