//
// Created by Alexandre Taillet on 15/03/2024.
//

#include "light.h"

#include <iostream>
#include <string>


static unsigned int inc;
static int staticID;
Light::Light(glm::vec3 pos,LightType type,glm::vec3 color, float ambiant, float diffuse, float specular) {
    currentID = staticID;
    staticID++;
    Light::pos = pos;
    Light::type = type;
    Light::ambiant = ambiant;
    Light::diffuse = diffuse;
    Light::specular = specular;
    Light::color = color;
}

void Light::SetupShader(ProgramShader *shader) {
    std::string namePath = "lights["+std::to_string(currentID)+"]";
    //std::cout << pos.x << " " << pos.z << std::endl;
    //std::cout << namePath +".position" << std::endl;
    shader->setVec3(namePath+".position",pos);
    shader->setVec3(namePath +".color",color);
    shader->setFloat(namePath+".ambient",ambiant);
    shader->setFloat(namePath+".diffuse",diffuse);
    shader->setFloat(namePath+".specular",specular);
    if(hasBeenInit) return;
    inc++;
    shader->setInt("lightSize",inc);
    hasBeenInit = true;
}


void Light::Clear() {
    inc = 0;
}

int Light::getStaticID() {
    return staticID;
}
