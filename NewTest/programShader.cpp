#include "programShader.h"

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>
#include <glad/glad.h>



ProgramShader::ProgramShader(unsigned int _program): program(_program)

{
    std::cout << "creating program object with "+ std::to_string(program) <<  std::endl;
}


int ProgramShader::add(unsigned int shader)
{
    std::cout << "Add shader " << std::to_string(shader) << " in program " << std::to_string(program) << std::endl;
    
    shaders.push_back(shader);
    return shaders.size()-1;
}

void ProgramShader::enable(int index)
{
    unsigned int shader = shaders.at(index);
    std::cout << "Attach shader " << std::to_string(shader) << std::endl;
    glAttachShader(program,shader);
}

void ProgramShader::enableAll()
{
    std::cout << "EnableALL for program " + std::to_string(program) << std::endl;
    for (int i = 0; i < shaders.size(); ++i)
    {
        std::cout << (std::to_string(i)) << std::endl;
        enable(i);
    }
    glLinkProgram(program);
}

void ProgramShader::disable(int index)
{
    unsigned int shader = shaders.at(index);
    glDetachShader(program,shader);
}

void ProgramShader::disableAll()
{
    for (int i = 0; i < shaders.size(); ++i)
    {
        disable(i);
    }
}

void ProgramShader::remove(int index)
{
    unsigned int shader = shaders.at(index);
    glDeleteShader(program);
}

unsigned int ProgramShader::getID()
{
    std::cout << "Program ID CHANGED ???" << std::to_string(program) + "\n";
    return program;
}

void ProgramShader::use()
{
    glUseProgram(program);
}


