#version 330 core


layout (location = 0) in vec3 aPos;
out vec3 color;

uniform mat4 model;
uniform mat4 camMatrix;



void main(){
    //gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
    gl_Position =camMatrix * model * vec4(aPos,1);
}