#pragma once
#include <filesystem>
#include <iostream>
#include <string>
#include <glad/glad.h>

#include "programShader.h"


class Texture
{
public:
    Texture(const char* path, const char* fileName, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
    Texture(const char* path, const char* fileName, GLenum slot) : Texture::Texture(path, fileName,GL_TEXTURE_2D, slot, GL_RGBA, GL_UNSIGNED_BYTE) {};
    GLuint ID;
    GLenum type;
    GLuint unit;
    int widthImg, heightImg, numColCh;
    static const char* AssetsPath()
    {
        std::string parentDir = (std::filesystem::current_path().parent_path()).string();
        std::cout << parentDir << std::endl;
        std::string texPath = "/NewTest/textures/";
        std::cout << "FUCKYOU " << (parentDir+texPath).c_str() << std::endl;
        // Dynamically allocate memory for the C-style string
        size_t bufferSize = parentDir.length() + texPath.length() + 1;
        char* result = new char[bufferSize];

        // Use strcpy_s instead of strcpy
        strcpy_s(result, bufferSize, (parentDir + texPath).c_str());

        return result;
    }
    static void BlendAlphaChannel();
    void texUnit(ProgramShader* shader, const char* uniform, GLuint unit);
    void Bind();
    void Unbind();
    void Delete();
};
