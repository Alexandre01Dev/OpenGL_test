//
// Created by Alexandre Taillet on 15/03/2024.
//

#include "mesh.h"

#include "ebo.h"
#include "vao.h"

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, std::vector<Texture>& textures)
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

void Mesh::Draw(ProgramShader *shader, Camera &camera,
    glm::mat4 matrix,
    glm::vec3 translation,
    glm::quat rotation,
    glm::vec3 scale,
    bool reverse_rot) {
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
    // Initialize matrices
    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 rot = glm::mat4(1.0f);
    glm::mat4 sca = glm::mat4(1.0f);

    // Transform the matrices to their correct form
    trans = glm::translate(trans, translation);
    rot = glm::mat4_cast(rotation);
    if(reverse_rot)
        rot = -rot;

    sca = glm::scale(sca, scale);


    glUniformMatrix4fv(glGetUniformLocation(shader->getID(),"translation"),1,GL_FALSE, glm::value_ptr(trans));
    glUniformMatrix4fv(glGetUniformLocation(shader->getID(),"rotation"),1,GL_FALSE, glm::value_ptr(rot));
    glUniformMatrix4fv(glGetUniformLocation(shader->getID(),"scale"),1,GL_FALSE, glm::value_ptr(sca));
    glUniformMatrix4fv(glGetUniformLocation(shader->getID(),"model"),1,GL_FALSE, glm::value_ptr(matrix));



    // Draw the actual mesh
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

