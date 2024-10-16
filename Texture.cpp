#include "texture.h"
#include <iostream>

Texture::Texture(int texSize, const char** texFile)
    : m_texSize{texSize}, m_texFile{texFile}
{
    m_textures = new GLuint[texSize];
    glGenTextures(m_texSize, m_textures);
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    const char* fileName;
    unsigned char* data;

    for (int i{ 0 }; i < m_texSize; ++i)
    {
        glBindTexture(GL_TEXTURE_2D, m_textures[i]);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        fileName = m_texFile[i];
        data = stbi_load(fileName, &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }


}

void Texture::bindTexture(int textureID) const
{
    glBindTexture(GL_TEXTURE_2D, m_textures[textureID]);
}