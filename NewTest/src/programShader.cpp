#include "programShader.h"

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>


ProgramShader::ProgramShader(unsigned int _program):
program(_program)
{
    //std::cout << "creating program object with "+ std::to_string(program) <<  std::endl;
}


int ProgramShader::add(unsigned int shader)
{
    //std::cout << "Add shader " << std::to_string(shader) << " in program " << std::to_string(program) << std::endl;
    //std::cout << "list size " << std::to_string(shaders.size()) << std::endl;
    shaders.push_back(shader);
  //  std::cout << "list size " << std::to_string(shaders.size()) << std::endl;
    
    return shaders.size()-1;
}

void ProgramShader::enable(int index)
{
    unsigned int shader = shaders.at(index);
   // std::cout << "Attach shader " << std::to_string(shader) << std::endl;
    glAttachShader(program,shader);
   // remove(index);
}

void ProgramShader::enableAll()
{
    
    std::cout << "EnableALL " << std::to_string(shaders.size()) << " shaders for program " + std::to_string(program) << std::endl;
    for (int i = 0; i < shaders.size(); ++i)
    {
    //    std::cout << (std::to_string(i)) << std::endl;
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
    glDeleteShader(shader);
}

void ProgramShader::removeAll()
{
    for (int i = 0; i < shaders.size(); ++i)
    {
        remove(i);
    }
}

unsigned int ProgramShader::getID() const
{
   // std::cout << "Program ID CHANGED ???" << std::to_string(program) + "\n";
    return program;
}

void ProgramShader::use()
{
    glUseProgram(program);

}


void ProgramShader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}
void ProgramShader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

void ProgramShader::setVec2(const std::string &name, glm::vec2 value) const
{
    glUniform2f(glGetUniformLocation(program, name.c_str()), value.x,value.y);
}
void ProgramShader::setVec3(const std::string &name, glm::vec3 value) const
{
    glUniform3f(glGetUniformLocation(program, name.c_str()), value.x,value.y,value.z);
}

void ProgramShader::setVec4(const std::string &name, glm::vec4 value) const
{
    glUniform4f(glGetUniformLocation(program, name.c_str()), value.x,value.y,value.z,value.w);
}
void ProgramShader::setMat2(const std::string &name, GLsizei count, GLboolean transpose, glm::mat2 value) const
{
    glUniformMatrix2fv(glGetUniformLocation(program, name.c_str()),count,transpose,glm::value_ptr(value));
}
void ProgramShader::setMat3(const std::string &name, GLsizei count, GLboolean transpose, glm::mat3 value) const
{
    glUniformMatrix3fv(glGetUniformLocation(program, name.c_str()),count,transpose,glm::value_ptr(value));
}

void ProgramShader::setMat4(const std::string &name, GLsizei count, GLboolean transpose, glm::mat4 value) const
{
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()),count,transpose,glm::value_ptr(value));
}

