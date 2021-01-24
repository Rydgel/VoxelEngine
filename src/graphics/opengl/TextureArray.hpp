#ifndef VOXELSENGINE_TEXTURE_HPP
#define VOXELSENGINE_TEXTURE_HPP

#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF

#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

struct TextureArray
{
    explicit TextureArray();
    ~TextureArray();

    TextureArray(const TextureArray & textureArray) = delete;
    TextureArray & operator=(TextureArray & other) = delete;
    TextureArray(TextureArray && other) noexcept = delete;
    TextureArray & operator=(TextureArray && other) noexcept = delete;

    void add(std::vector<std::string> paths);

    void bind();
    void unbind();

private:

    unsigned int id_;
    int textureNumber_ = 0;
};


#endif //VOXELSENGINE_TEXTURE_HPP
