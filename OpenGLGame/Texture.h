#pragma once
#include "stb_image.h"
#include"glad/glad.h"

class Texture
{
public: 
    
    
    unsigned int textureId;
    Texture(const char*imagepath, int textureUnit) {
    int width, height, nrChannels;

    unsigned char* data = stbi_load(imagepath,
        &width, &height, &nrChannels, 0);


    glActiveTexture(textureUnit);
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width,
        height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

};

