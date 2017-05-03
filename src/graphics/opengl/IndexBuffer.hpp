#ifndef VOXELSENGINE_INDEXBUFFER_H
#define VOXELSENGINE_INDEXBUFFER_H

#include "Buffer.hpp"

struct IndexBuffer : public Buffer
{
    IndexBuffer() : Buffer(GL_ELEMENT_ARRAY_BUFFER) {};
};

#endif //VOXELSENGINE_INDEXBUFFER_H
