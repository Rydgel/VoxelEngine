#include "TextureArray.hpp"
#include <stb_image.hpp>
#include <glad.h>

TextureArray::TextureArray()
{
    glGenTextures(1, &id_);
}

TextureArray::~TextureArray()
{
    glDeleteTextures(1, &id_);
}

void TextureArray::add(std::vector<std::string> paths)
{
    bind();
    int mipLevelCount = 4;
    auto layerCount = static_cast<GLsizei>(paths.size());
    // glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, 16, 16, layerCount, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexStorage3D(GL_TEXTURE_2D_ARRAY, mipLevelCount, GL_RGBA8, 16, 16,  layerCount);

    for (auto & path : paths) {
        int width, height, nbChannels;
        unsigned char* image = stbi_load(path.c_str(), &width, &height, &nbChannels, STBI_rgb_alpha);
        if (image == nullptr) throw(std::string("Failed to load texture"));
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, textureNumber_, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, image);
        textureNumber_ ++;
        stbi_image_free(image);
    }

    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // todo need to test for driver support
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
    unbind();
}

void TextureArray::bind()
{
    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, id_);
}

void TextureArray::unbind()
{
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}