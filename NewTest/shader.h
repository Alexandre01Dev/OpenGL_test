#pragma once
#include <string>
#include <glad/glad.h>

#include "programShader.h"



class Shader
{
    public:
    std::string loadShaderSrc(const char* filename);
    GLuint ID;
    Shader(const char* vertexFile, const char* fragmentFile);
    void ActivateALL();
    void ActivateALL(unsigned int ID);
    void Delete();
    ProgramShader& getProgram(unsigned int ID);
    ProgramShader& loadShader(std::string& code,GLenum type, int count, unsigned int programID);
};
