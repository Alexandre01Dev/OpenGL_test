//
// Created by Alexandre Taillet on 15/03/2024.
//

#ifndef LIGHT_H
#define LIGHT_H
#include <glm/vec3.hpp>

#include "programShader.h"


class Light {

    public:
        enum LightType {
            POINT,
            DIRECTIONAL,
            SPECULAR
        };
        static int getStaticID();

        glm::vec3 pos;
        bool hasBeenInit = false;
        LightType type;
        unsigned int currentID;
        float diffuse;
        float ambiant;
        float specular;
        glm::vec3 color;
        Light(glm::vec3 pos, LightType type,glm::vec3 color, float ambiant, float diffuse, float specular);
        void SetupShader(ProgramShader* shader);
        void Clear();
};



#endif //LIGHT_H
