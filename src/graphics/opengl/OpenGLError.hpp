#ifndef VOXELSENGINE_OPENGLERROR_HPP
#define VOXELSENGINE_OPENGLERROR_HPP

#include <iostream>
#include <GLFW/glfw3.h>

struct OpenGLError
{
    const char * glErrorString(GLenum err);
    bool isOpenGLError();
    void checkOpenGLError(std::string error);
};


#endif //VOXELSENGINE_OPENGLERROR_HPP
