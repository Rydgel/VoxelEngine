#ifndef VOXELSENGINE_INPUTMANAGER_HPP
#define VOXELSENGINE_INPUTMANAGER_HPP

#include <unordered_map>
#include <array>
#include <GLFW/glfw3.h>

struct MousePosition
{
    double xPos = 0;
    double yPos = 0;
};

struct InputManager
{
    void keyPushed(int key);
    void keyReleased(int key);
    int getKeyState(int key);
    void setMousePosition(double xpos, double ypos);
    void mousePushed(int button);
    void mouseReleased(int button);
    int getMouseState(int button);
    const MousePosition getMousePosition();

private:

    std::unordered_map<int, bool> keyStates_ {};
    std::unordered_map<int, bool> mouseStates_ {};
    MousePosition mousePosition_ {};
};


#endif //VOXELSENGINE_INPUTMANAGER_HPP
