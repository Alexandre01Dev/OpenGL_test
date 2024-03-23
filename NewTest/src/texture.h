#pragma once
#include <filesystem>
#include <iostream>
#include <string>
#include <glad/glad.h>
#define _CRT_SECURE_NO_WARNINGS  // Disable warnings in Visual Studio
#include <stdio.h>

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
    Texture(const char* path, const char* fileName, TexType texType, GLenum slot, GLenum format, GLenum pixelType);
    Texture(const char* path, const char* fileName, GLenum slot,TexType texType) : Texture::Texture(path, fileName,texType, slot, GL_RGBA, GL_UNSIGNED_BYTE) {};
    GLuint ID;
    TexType type;
    GLuint unit;
    int widthImg, heightImg, numColCh;
    static const char* AssetsPath()
    {
        std::string parentDir = (std::__fs::filesystem::current_path().parent_path()).string();
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
};
