#include "InputManager.hpp"

void InputManager::keyPushed(int key)
{
    keyStates_[key] = true;
}

void InputManager::keyReleased(int key)
{
    keyStates_[key] = false;
}

int InputManager::getKeyState(int key)
{
    return keyStates_[key];
}

void InputManager::setMousePosition(double xpos, double ypos)
{
    mousePosition_.xPos = xpos;
    mousePosition_.yPos = ypos;
}

void InputManager::mousePushed(int button)
{
    mouseStates_[button] = true;
}

void InputManager::mouseReleased(int button)
{
    mouseStates_[button] = false;
}

int InputManager::getMouseState(int button)
{
    return mouseStates_[button];
}

const MousePosition InputManager::getMousePosition()
{
    return mousePosition_;
}