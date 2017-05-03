#ifndef VOXELSENGINE_ARRAYBUFFER_HPP
#define VOXELSENGINE_ARRAYBUFFER_HPP

#include "Buffer.hpp"

struct ArrayBuffer : public Buffer
{
    ArrayBuffer() : Buffer(GL_ARRAY_BUFFER) {};
};


#endif //VOXELSENGINE_ARRAYBUFFER_HPP
