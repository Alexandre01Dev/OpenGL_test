#pragma once


#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texUV;
};
class VBO
{
    public:
        GLuint ID;
        VBO(std::vector<Vertex>& vertices, GLsizeiptr size);

        void Bind();
        void Unbind();
        void Delete();
    
};
