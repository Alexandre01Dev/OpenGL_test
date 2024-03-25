//
// Created by Alexandre Taillet on 15/03/2024.
//

#include "light.h"

#include <iostream>
#include <string>
#include <array>


static unsigned int inc;
static int staticID;
bool special = false;
Light::Light(glm::vec3 pos,LightType type,glm::vec3 color, float ambiant, float diffuse, float specular) {
    currentID = staticID;
    staticID++;
    Light::pos = pos;
    Light::type = type;
    Light::ambiant = ambiant;
    Light::diffuse = diffuse;
    Light::specular = specular;
    std::cout<< "Hello" << std::endl;
    Light::color = new std::array<float,3>{color.r,color.g,color.b};
    std::cout<< "Set color" << std::endl;
}




Light::Light(glm::vec3 pos, Light::LightType type, std::array<float, 3>& color, float ambiant, float diffuse, float specular)
        : pos(pos), type(type), color(&color), ambiant(ambiant), diffuse(diffuse), specular(specular) {
    std::cout << "Old Color "<< &color << std::endl;
    std::cout << "New Color "<< Light::color << std::endl;
    special = true;
    currentID = staticID;
    staticID++;
}



void Light::SetupShader(ProgramShader *shader) {
    std::string namePath = "lights["+std::to_string(currentID)+"]";
    //std::cout << pos.x << " " << pos.z << std::endl;
    //std::cout << namePath +".position" << std::endl;
    if(color == nullptr)
        return;

    shader->setVec3(namePath+".position",pos);

    shader->setVec3(namePath +".color",color->data());

    shader->setFloat(namePath+".ambient",ambiant);
    shader->setFloat(namePath+".diffuse",diffuse);
    shader->setFloat(namePath+".specular",specular);
    if(hasBeenInit) return;
    inc++;
    shader->setInt("lightSize",inc);
    hasBeenInit = true;
    if(special)
        std::cout << "Color from " << color << " " << *color->data() << std::endl;
}


void Light::Clear() {
    inc = 0;
}

int Light::getStaticID() {
    return staticID;
}


