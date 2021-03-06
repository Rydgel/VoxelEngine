#ifndef VOXELSENGINE_MESH_HPP
#define VOXELSENGINE_MESH_HPP

#include <vector>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "Vertex.hpp"

struct Mesh
{
    std::vector<Vertex> vertices {};
    std::vector<GLuint> indices {};

    inline GLuint verticesSize() const
    {
        return static_cast<GLuint>(vertices.size());
    }
};


#endif //VOXELSENGINE_MESH_HPP
