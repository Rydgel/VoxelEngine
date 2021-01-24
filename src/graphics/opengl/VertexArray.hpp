#ifndef VOXELSENGINE_VERTEXARRAY_HPP
#define VOXELSENGINE_VERTEXARRAY_HPP

#include <glad/gl.h>
#include <GLFW/glfw3.h>

struct VertexArray
{
    VertexArray();
    ~VertexArray();

    VertexArray(const VertexArray & vertexArray) = delete;
    VertexArray & operator=(VertexArray & vertexArray) = delete;
    VertexArray(VertexArray && vertexArray) noexcept;
    VertexArray & operator=(VertexArray && vertexArray) noexcept;

    void bind() const;
    void unbind() const;

private:

    GLuint id_ = 0;
};


#endif //VOXELSENGINE_VERTEXARRAY_HPP
