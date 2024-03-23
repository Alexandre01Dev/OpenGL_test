#pragma once
#include <string>
#include <glad/glad.h>

#include "programShader.h"



class Shaders
{
    public:
    std::string loadShaderSrc(const char* filename);
    GLuint ID;
    Shaders();
    void ActivateALL();
    void ActivateALL(unsigned int ID);
    void Delete();
    ProgramShader* getProgram(unsigned int ID);
    ProgramShader* loadShader(const char* vertexFile, const char* fragmentFile,unsigned int programID);
    private:
    ProgramShader* loadShader(std::string& code,GLenum type, int count, unsigned int programID);
};
