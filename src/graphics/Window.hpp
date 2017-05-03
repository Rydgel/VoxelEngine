#ifndef VOXELSENGINE_WINDOW_HPP
#define VOXELSENGINE_WINDOW_HPP

#include <GLFW/glfw3.h>
#include <memory>
#include "InputManager.hpp"


struct Window
{
    struct DestroyglfwWin
    { void operator()(GLFWwindow *ptr) { glfwDestroyWindow(ptr); } };
    using GLFWwindowPtr = std::unique_ptr<GLFWwindow, DestroyglfwWin>;

    Window(InputManager & im, int width, int height, const char *title);
    ~Window();
    Window(const Window & window) = delete;
    Window & operator=(Window & window) = delete;
    Window(Window && window) noexcept = delete;
    Window & operator=(Window && window) noexcept = delete;

    void pollEvents();
    bool isOpen();
    void swapBuffers();
    void closeWindow();
    void changeTitle(const char *title);
    void hideCursor();
    void showCursor();
    void printGLInfos();

private:

    GLFWwindowPtr window_;
    InputManager & inputManager_;
    void setupEventCallbacks();
    void onKeyboardEvent(int key, int scancode, int action, int mods);
    void onMouseEvent(int button, int action, int mods);
};


#endif //VOXELSENGINE_WINDOW_HPP
