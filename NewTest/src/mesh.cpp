//
// Created by Alexandre Taillet on 15/03/2024.
//

#include "mesh.h"

#include "ebo.h"
#include "vao.h"

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, std::vector<Texture> &textures)
{
    Mesh::vertices = vertices;
    Mesh::indices = indices;
    Mesh::textures = textures;
    VAO.Bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO EBO(indices, sizeof(indices));

    // Links VBO to VAO
    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
    VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();
}

void Mesh::Draw(ProgramShader *shader, Camera &camera)
{
    shader->use();
    VAO.Bind();

    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        std::string num;
        TexType type = textures[i].type;
        if(type == DIFFUSE) {
            num = std::to_string(numDiffuse++);
        }else {
            num = std::to_string(numSpecular++);
        }
        textures[i].texUnit(shader,(Texture::texTypeToString(type) + num).c_str(),i);

        textures[i].Bind();
    }
    glUniform3f(glGetUniformLocation(shader->getID(),"camPos"), camera.position.x, camera.position.y, camera.position.z);
    camera.Matrix(shader,"camMatrix");
    // Draw the actual mesh
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
