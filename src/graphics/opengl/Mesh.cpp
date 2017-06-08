#include "Mesh.hpp"
#include <ostream>

void Mesh::addPosition(const glm::vec3 position)
{
    positions_.push_back(position);
}

void Mesh::addIndices(const GLuint indice)
{
    indices_.push_back(indice);
}

void Mesh::addNormal(const glm::vec3 normal)
{
    normals_.push_back(normal);
}

void Mesh::addUvs(const glm::vec3 uv)
{
    uvs_.push_back(uv);
}

void Mesh::addColors(const glm::vec3 color)
{
    colors_.push_back(color);
}

const std::vector<glm::vec3> Mesh::getPositions() const
{
    return positions_;
}

const std::vector<GLuint> Mesh::getIndices() const
{
    return indices_;
}

const std::vector<glm::vec3> Mesh::getNormals() const
{
    return normals_;
}

const std::vector<glm::vec3> Mesh::getUvs() const
{
    return uvs_;
}

const std::vector<glm::vec3> Mesh::getColors() const
{
    return colors_;
}
