#include "shader.h"

#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>

#include "programShader.h"

std::map<unsigned int,ProgramShader> programs = std::map<unsigned int, ProgramShader>();
int success;
char infoLog[512];



Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    std::string vertexCode = loadShaderSrc(vertexFile);
    std::string fragmentCode = loadShaderSrc(fragmentFile);

   
    loadShader(fragmentCode,GL_FRAGMENT_SHADER,1,0);
    loadShader(vertexCode,GL_VERTEX_SHADER,1,0);
}

ProgramShader& Shader::loadShader(std::string& code,GLenum type, int count, unsigned int programID)
{
    // compile shader
    unsigned int shader = glCreateShader(type);
    const GLchar* glChar = code.c_str();
    glShaderSource(shader,count,&glChar,NULL);
    glCompileShader(shader);

    std::cout << "Compiled shader "+ std::to_string(shader) << std::endl;
    ProgramShader* programptr = nullptr;
    // create program (shader)
    if(!programs.count(programID))
    {
        unsigned int shaderProgram;
        shaderProgram = glCreateProgram();
        std::cout << "new shader program " + std::to_string(shaderProgram) << std::endl;
        ProgramShader program =  ProgramShader(shaderProgram);
        program.add(shader);
       // glLinkProgram(shaderProgram);
        std::cout << "Place "+ std::to_string(programID) << std::endl;
        programs.emplace(programID,program);
        programptr = &program;
    }else {
        std::cout << "Program " << std::to_string(programID) << " deja present " << std::endl;
        ProgramShader program = programs.at(programID);
        std::cout << "Program ID ? " << std::to_string(program.getID()) << std::endl;
        program.add(shader);
        programptr = &program;
    }
   
    
    // catch error
    glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(shader,512,NULL,infoLog);
        std::cout << "Error with vertex shader comp.:" << std::endl << infoLog << std::endl;
    }
    return *programptr;
}

void Shader::ActivateALL()
{
    
}

void Shader::ActivateALL(unsigned ID)
{
}

void Shader::Delete()
{
}

ProgramShader& Shader::getProgram(unsigned int ID) {
    return programs.at(ID);
}




std::string Shader::loadShaderSrc(const char* filename)
{
    std::ifstream file;
    std::stringstream buf;

    std::string ret = "";

    file.open(filename);

    if(file.is_open())
    {
        buf << file.rdbuf();
        ret = buf.str();
    }else
    {
        std::cout << "Could not open " << filename << std::endl;
    }
    return ret;
}

