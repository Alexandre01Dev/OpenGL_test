#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/fwd.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

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
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, glm::vec2 value) const;
    void setVec3(const std::string &name, glm::vec3 value) const;
    void setVec4(const std::string &name, glm::vec4 value) const;
    void setMat2(const std::string &name, GLsizei count, GLboolean transpose, glm::mat2 value) const;
    void setMat3(const std::string &name, GLsizei count, GLboolean transpose, glm::mat3 value) const;
    void setMat4(const std::string &name, GLsizei count, GLboolean transpose, glm::mat4 value) const;
};
