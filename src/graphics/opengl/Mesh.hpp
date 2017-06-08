#ifndef VOXELSENGINE_MESH_HPP
#define VOXELSENGINE_MESH_HPP

#include <vector>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include "VertexAttribute.hpp"

struct Mesh
{
    void addPosition(glm::vec3 position);
    void addIndices(GLuint indice);
    void addNormal(glm::vec3 normal);
    void addUvs(glm::vec3 uv);
    void addColors(glm::vec3 color);

    const std::vector<glm::vec3> getPositions() const;
    const std::vector<GLuint> getIndices() const;
    const std::vector<glm::vec3> getNormals() const;
    const std::vector<glm::vec3> getUvs() const;
    const std::vector<glm::vec3> getColors() const;

private:

    std::vector<glm::vec3> positions_ {};
    std::vector<GLuint> indices_ {};
    std::vector<glm::vec3> normals_ {};
    std::vector<glm::vec3> uvs_ {};
    std::vector<glm::vec3> colors_ {};
};


#endif //VOXELSENGINE_MESH_HPP
