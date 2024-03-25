#include "texture.h"

#include <filesystem>
#include <iostream>
#include <stb/stb_image.h>

#include "programShader.h"



Texture::Texture(const char* path, const char* fileName, const TexType texType, GLenum slot, GLenum format, GLenum pixelType)
{
    type = texType;
    stbi_set_flip_vertically_on_load(true);
    std::string fullPathName = std::string(path) + fileName;
    std::cout << path << fileName << std::endl;
    std::cout << fullPathName << std::endl;
    int desired_channel = 0;
    if(format == GL_RGBA)
    {
        desired_channel = STBI_rgb_alpha;
    }
    unsigned char* bytes = stbi_load(fullPathName.c_str(),&widthImg,&heightImg, &numColCh,  desired_channel);
    glGenTextures(1,&ID);
    std::cout << &ID;
    glActiveTexture(slot);
    glBindTexture(GL_TEXTURE_2D,ID);
    // resolution of the texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    unit = slot;
    //repetion of the texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    // format GL_RGBA
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);

    // Generate Midmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // Free image in RAM
    stbi_image_free(bytes);

    glBindTexture(GL_TEXTURE_2D, 0);
    delete[] path;
}




void Texture::BlendAlphaChannel()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Texture::texUnit(ProgramShader* shader, const char* uniform, GLuint unit)
{
    GLuint texUni = glGetUniformLocation(shader->getID(),uniform);
    shader->use();
    glUniform1i(texUni,unit);
}

void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}
