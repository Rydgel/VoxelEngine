#include "Chunk.hpp"

Chunk::Chunk(int id, glm::vec3 offset)
{
    chunkId_ = id;
    offset_ = offset;

    // todo replace by air
    voxels_.fill(std::make_shared<Voxel>(VoxelType::GRASS));
}

const glm::vec3 Chunk::getOffset() const
{
    return offset_;
}

void Chunk::meshing()
{
    chunkMesh_.addPosition({1, 0, 0});
    chunkMesh_.addPosition({0, 0, 0});
    chunkMesh_.addPosition({0, 1, 0});
    chunkMesh_.addPosition({1, 1, 0});

    chunkMesh_.addPosition({1, 0, 1});
    chunkMesh_.addPosition({1, 0, 0});
    chunkMesh_.addPosition({1, 1, 0});
    chunkMesh_.addPosition({1, 1, 1});

    chunkMesh_.addPosition({0, 0, 1});
    chunkMesh_.addPosition({1, 0, 1});
    chunkMesh_.addPosition({1, 1, 1});
    chunkMesh_.addPosition({0, 1, 1});

    chunkMesh_.addPosition({0, 0, 0});
    chunkMesh_.addPosition({0, 0, 1});
    chunkMesh_.addPosition({0, 1, 1});
    chunkMesh_.addPosition({0, 1, 0});

    chunkMesh_.addPosition({0, 1, 1});
    chunkMesh_.addPosition({1, 1, 1});
    chunkMesh_.addPosition({1, 1, 0});
    chunkMesh_.addPosition({0, 1, 0});

    chunkMesh_.addPosition({0, 0, 0});
    chunkMesh_.addPosition({1, 0, 0});
    chunkMesh_.addPosition({1, 0, 1});
    chunkMesh_.addPosition({0, 0, 1});

    chunkMesh_.addIndices(0); chunkMesh_.addIndices(1); chunkMesh_.addIndices(2);
    chunkMesh_.addIndices(2); chunkMesh_.addIndices(3); chunkMesh_.addIndices(0);

    chunkMesh_.addIndices(4); chunkMesh_.addIndices(5); chunkMesh_.addIndices(6);
    chunkMesh_.addIndices(6); chunkMesh_.addIndices(7); chunkMesh_.addIndices(4);

    chunkMesh_.addIndices(8); chunkMesh_.addIndices(9); chunkMesh_.addIndices(10);
    chunkMesh_.addIndices(10); chunkMesh_.addIndices(11); chunkMesh_.addIndices(8);

    chunkMesh_.addIndices(12); chunkMesh_.addIndices(13); chunkMesh_.addIndices(14);
    chunkMesh_.addIndices(14); chunkMesh_.addIndices(15); chunkMesh_.addIndices(12);

    chunkMesh_.addIndices(16); chunkMesh_.addIndices(17); chunkMesh_.addIndices(18);
    chunkMesh_.addIndices(18); chunkMesh_.addIndices(19); chunkMesh_.addIndices(16);

    chunkMesh_.addIndices(20); chunkMesh_.addIndices(21); chunkMesh_.addIndices(22);
    chunkMesh_.addIndices(22); chunkMesh_.addIndices(23); chunkMesh_.addIndices(20);

    chunkMesh_.addColors({0, 0, 1});
    chunkMesh_.addColors({0, 0, 0});
    chunkMesh_.addColors({0, 1, 0});
    chunkMesh_.addColors({1, 1, 0});

    chunkMesh_.addColors({1, 0, 1});
    chunkMesh_.addColors({1, 0, 0});
    chunkMesh_.addColors({1, 1, 0});
    chunkMesh_.addColors({1, 1, 1});

    chunkMesh_.addColors({0, 0, 1});
    chunkMesh_.addColors({1, 0, 1});
    chunkMesh_.addColors({1, 1, 1});
    chunkMesh_.addColors({0, 1, 1});

    chunkMesh_.addColors({0, 0, 0});
    chunkMesh_.addColors({0, 0, 1});
    chunkMesh_.addColors({0, 1, 1});
    chunkMesh_.addColors({0, 1, 0});

    chunkMesh_.addColors({0, 1, 1});
    chunkMesh_.addColors({1, 1, 1});
    chunkMesh_.addColors({1, 1, 0});
    chunkMesh_.addColors({0, 1, 0});

    chunkMesh_.addColors({0, 0, 0});
    chunkMesh_.addColors({1, 0, 0});
    chunkMesh_.addColors({1, 0, 1});
    chunkMesh_.addColors({0, 0, 1});

    chunkMesh_.addNormal({0, 0, -1});
    chunkMesh_.addNormal({0, 0, -1});
    chunkMesh_.addNormal({0, 0, -1});
    chunkMesh_.addNormal({0, 0, -1});

    chunkMesh_.addNormal({1, 0, 0});
    chunkMesh_.addNormal({1, 0, 0});
    chunkMesh_.addNormal({1, 0, 0});
    chunkMesh_.addNormal({1, 0, 0});

    chunkMesh_.addNormal({0, 0, 1});
    chunkMesh_.addNormal({0, 0, 1});
    chunkMesh_.addNormal({0, 0, 1});
    chunkMesh_.addNormal({0, 0, 1});

    chunkMesh_.addNormal({-1, 0, 0});
    chunkMesh_.addNormal({-1, 0, 0});
    chunkMesh_.addNormal({-1, 0, 0});
    chunkMesh_.addNormal({-1, 0, 0});

    chunkMesh_.addNormal({0, 1, 0});
    chunkMesh_.addNormal({0, 1, 0});
    chunkMesh_.addNormal({0, 1, 0});
    chunkMesh_.addNormal({0, 1, 0});

    chunkMesh_.addNormal({0, -1, 0});
    chunkMesh_.addNormal({0, -1, 0});
    chunkMesh_.addNormal({0, -1, 0});
    chunkMesh_.addNormal({0, -1, 0});


    vertexArray_.bind();

    positionsBuffer_.bind();
    positionsBuffer_.setData(chunkMesh_.getPositions(), Usage::Static);
    normalsBuffer_.bind();
    normalsBuffer_.setData(chunkMesh_.getNormals(), Usage::Static);
    colorsBuffer_.bind();
    colorsBuffer_.setData(chunkMesh_.getColors(), Usage::Static);
    indicesBuffer_.bind();
    indicesBuffer_.setData(chunkMesh_.getIndices(), Usage::Static);

    glEnableVertexAttribArray(0);
    positionsBuffer_.bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);

    glEnableVertexAttribArray(1);
    colorsBuffer_.bind();
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);

    glEnableVertexAttribArray(2);
    normalsBuffer_.bind();
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);

    unbind();

    needMeshing = false;
}

void Chunk::bind()
{
    vertexArray_.bind();
    indicesBuffer_.bind();
    positionsBuffer_.bind();
}

void Chunk::unbind()
{
    indicesBuffer_.unbind();
    positionsBuffer_.unbind();
    vertexArray_.unbind();
}

void Chunk::draw()
{
    if (needMeshing) {
        meshing();
    }

    bind();
    // todo draw
    auto indicesSize = static_cast<GLsizei>(chunkMesh_.getIndices().size());
    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLES, 0, 36);
    unbind();
}