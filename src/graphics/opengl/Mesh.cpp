#include "Mesh.hpp"
#include <ostream>

std::ostream& operator<<(std::ostream& os, const Face face)
{
    switch(face)
    {
        case Face::front : return os << "front";
        case Face::back  : return os << "back";
        case Face::top   : return os << "top";
        case Face::bottom: return os << "bottom";
        case Face::right : return os << "right";
        case Face::left  : return os << "left";
    }
    assert(false);
    return os << "ERROR";
}

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

void Mesh::addUvs(const glm::vec2 uv)
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

const std::vector<glm::vec2> Mesh::getUvs() const
{
    return uvs_;
}

const std::vector<glm::vec3> Mesh::getColors() const
{
    return colors_;
}
