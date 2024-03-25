#include "shaders.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>

#include "programShader.h"

std::map<unsigned int,ProgramShader*> programs = std::map<unsigned int, ProgramShader*>();
int success;
char infoLog[512];



Shaders::Shaders()
{
    
}

ProgramShader* Shaders::loadShader(const char* vertexFile, const char* fragmentFile, unsigned programID)
{
    std::string vertexCode = loadShaderSrc(vertexFile);
    std::string fragmentCode = loadShaderSrc(fragmentFile);
    loadShader(fragmentCode,GL_FRAGMENT_SHADER,1,programID);
    loadShader(vertexCode,GL_VERTEX_SHADER,1,programID);
    return getProgram(programID);
}

ProgramShader* Shaders::loadShader(std::string& code,GLenum type, int count, unsigned int programID)
{
    // compile shader
    GLuint shader = glCreateShader(type);
    const GLchar* glChar = code.c_str();
    glShaderSource(shader,count,&glChar,NULL);
    glCompileShader(shader);

    std::cout << "Compiled shader "+ std::to_string(shader) << std::endl;
    ProgramShader* programptr;
    // create program (shader)
    if(!programs.count(programID))
    {
        unsigned int shaderProgram;
        shaderProgram = glCreateProgram();
        std::cout << "new shader program " + std::to_string(shaderProgram) << std::endl;
        ProgramShader* p =  new ProgramShader(shaderProgram);
        
        
        p->add(shader);
       // glLinkProgram(shaderProgram);
        std::cout << "Place "+ std::to_string(programID) << std::endl;
        programs[programID] = p;
        std::cout << "Place "+ std::to_string(p->getID()) << std::endl;
       // programs.emplace(programID,program);
        std::cout << "pointer " << p;
        programptr = p;
    }else {
        std::cout << "Program " << std::to_string(programID) << " deja present " << std::endl;
        ProgramShader* program = programs[programID];
        std::cout << "Program ID ? " << program->getID() << std::endl;
        program->add(shader);
        

        std::cout << "pointer" << programs[programID];
        //programs.emplace(programID,program);
        programptr = program;
    }
    
    //glAttachShader(programptr->getID(),shader);
    // catch error
    glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(shader,512,NULL,infoLog);
        std::cout << "Error with vertex shader comp.:" << std::endl << infoLog << std::endl;
    }
   
    //glDeleteShader(shader);
    
    return programptr;
}

void Shaders::ActivateALL()
{
    for (const auto& value : programs)
    {
        value.second->enableAll();
    }
}

void Shaders::ActivateALL(unsigned ID)
{
    programs.at(ID)->enableAll();
}

void Shaders::Delete()
{
    for (const auto& value : programs)
    {
        ((ProgramShader) *value.second).removeAll();
    }
}

ProgramShader* Shaders::getProgram(unsigned int ID) {
    std::cout << std::endl <<  programs[ID] << " HUH" << std::endl;;
    return programs[ID];
}




std::string Shaders::loadShaderSrc(const char* filename)
{
    std::string parentDir = (std::filesystem::current_path()).string();
    std::cout << parentDir << std::endl;
    std::string texPath = "/";
    std::ifstream file;
    std::stringstream buf;

    std::string ret = "";

    file.open(parentDir+texPath+filename);

    if(file.is_open())
    {
        buf << file.rdbuf();
        ret = buf.str();
    }else
    {
        std::cout << "Could not open " << parentDir+texPath+filename << std::endl;
    }
    return ret;
}

