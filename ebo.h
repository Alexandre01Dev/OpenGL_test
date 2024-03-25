#pragma once


#include <vector>
#include <glad/glad.h>
class EBO
{
    public:
        GLuint ID;
        EBO(std::vector<GLuint>& indices, GLsizeiptr size);

        void Bind();
        void Unbind();
        void Delete();
};
