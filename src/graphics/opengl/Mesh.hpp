#ifndef VOXELSENGINE_MESH_HPP
#define VOXELSENGINE_MESH_HPP

#include <vector>
#include <GLFW/glfw3.h>
#include "Vertex.hpp"

struct Mesh
{
    std::vector<Vertex> vertices {};
    std::vector<GLuint> indices {};
};


#endif //VOXELSENGINE_MESH_HPP
