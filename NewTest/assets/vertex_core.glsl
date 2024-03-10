#version 330 core


layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNormal;
out vec3 color;

uniform float scale;
uniform float luminosity;
uniform vec3 shuffler;

uniform mat4 camMatrix;
uniform mat4 model;
out vec2 texCoord;
out vec3 normal;
out vec3 crntPos;

void main(){
    crntPos = vec3(model*vec4(aPos,1.0f));
    
    //gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
    gl_Position =camMatrix * model *  vec4(aPos,1.0f);
    //gl_Position = vec4(aPos,1);

 //   color = vec3(aColor.r,aColor.g,aColor.b);
    vec3 fColor = aColor;
    if (shuffler != vec3(0.0f, 0.0f,0.0f)) {
        //fColor = vec3(shuffler[0],shuffler[1],shuffler[2]);
        fColor.r += shuffler.r;
        fColor.g += shuffler.g;
        fColor.b += shuffler.b;
    }
    color = vec3(min(fColor.r*luminosity,3.0f), min(fColor.g*luminosity,3.0f), min(fColor.b*luminosity,3.0f));
    texCoord = aTex;
    
    normal = aNormal; 
}