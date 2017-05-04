#ifndef VOXELSENGINE_SHADER_HPP
#define VOXELSENGINE_SHADER_HPP

#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>

struct Shader
{
    // Constructor reads and builds the shader
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    // todo add all uniforms type
    // uniform variable settings
    void setUniform(const std::string &name, GLuint x);
    void setUniform(const std::string &name, int x);
    void setUniform(const std::string &name, float x);
    void setUniform(const std::string &name, glm::mat4 trans);
    void setUniform(const std::string &name, glm::vec3 vec);
    void setUniform(const std::string &name, glm::vec4 vec);
    // Use the program
    void bind();
    void unbind();

private:

    // The program ID
    GLuint program_;
};

#endif //VOXELSENGINE_SHADER_HPP
