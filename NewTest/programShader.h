#pragma once
#include <vector>
#include <glad/glad.h>

class ProgramShader
{
public:
    std::vector<unsigned int> shaders = std::vector<unsigned int>();
    const unsigned int program;
    ProgramShader(unsigned int program);
    int add(unsigned int shader);
    void enable(int index);
    void enableAll();
    void disable(int index);
    void disableAll();
    void remove(int index);
    void removeAll();
    unsigned int getID() const;
    void use();
};
