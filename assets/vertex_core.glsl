#version 330 core


layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;


out vec3 crntPos;
out vec3 normal;
out vec3 color;
out vec2 texCoord;

// import camera matrix
uniform mat4 camMatrix;
// import model matrix
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;



uniform float luminosity;
uniform vec3 shuffler;



void main(){
    crntPos = vec3(model * translation * rotation * scale * vec4(aPos, 1.0f));

    //gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);

    //gl_Position = vec4(aPos,1);

 //   color = vec3(aColor.r,aColor.g,aColor.b);
    vec3 fColor = aColor;
    normal = aNormal;
    if (shuffler != vec3(0.0f, 0.0f,0.0f)) {
        //fColor = vec3(shuffler[0],shuffler[1],shuffler[2]);
        fColor.r += shuffler.r;
        fColor.g += shuffler.g;
        fColor.b += shuffler.b;
    }
    color = vec3(min(fColor.r*luminosity,3.0f), min(fColor.g*luminosity,3.0f), min(fColor.b*luminosity,3.0f));
    texCoord = mat2(0.0f,-1.0f,1.0,0.0) * aTex;


    gl_Position = camMatrix * vec4(crntPos, 1.0);
}