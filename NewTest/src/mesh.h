//
// Created by Alexandre Taillet on 15/03/2024.
//

#ifndef MESH_H
#define MESH_H

#include <string>
#include "vao.h"
#include "camera.h"
#include "texture.h"


class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    VAO VAO;

    Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);

    void Draw(ProgramShader* shader,Camera& camera);
};



#endif //MESH_H
