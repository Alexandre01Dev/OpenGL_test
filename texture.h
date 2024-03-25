#pragma once
#include <filesystem>
#include <iostream>
#include <string>
#include <glad/glad.h>
#define _CRT_SECURE_NO_WARNINGS  // Disable warnings in Visual Studio
#include <stdio.h>
#include <string.h>

#include "programShader.h"

enum TexType {
    DIFFUSE,
    SPECULAR
};


class Texture
{
public:
    static std::string texTypeToString(TexType type) {
        switch (type) {
            case DIFFUSE:
                return "diffuse";
            case SPECULAR:
                return "specular";
            default:
                return "unknown";
        }
    }
    Texture(const char* path, const char* fileName,  GLenum slot,TexType texType, GLenum format, GLenum pixelType);
    Texture(const char* path, const char* fileName, GLenum slot,TexType texType, bool alphaChannel = false);
    GLuint ID;
    TexType type;
    GLuint unit;
    int widthImg, heightImg, numColCh;
    static const char* AssetsPath()
    {
        std::string parentDir = (std::filesystem::current_path()).string();
        std::cout << parentDir << std::endl;
        std::string texPath = "/textures/";
        // Dynamically allocate memory for the C-style string
        size_t bufferSize = parentDir.length() + texPath.length() + 1;
        char* result = new char[bufferSize];

        // Use strcpy_s instead of strcpy

        strcpy(result, (parentDir + texPath).c_str());
        return result;
    }
    static void BlendAlphaChannel();
    void texUnit(ProgramShader* shader, const char* uniform, GLuint unit);
    void Bind();
    void Unbind();
    void Delete();
private:
    unsigned char* loadTexture(const char* path, const char* fileName, bool alphaChannel);
    void loadInGL(GLenum slot,TexType texType, GLenum format, GLenum pixelType, unsigned char* bytes);
};
