#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>

#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include "programShader.h"


class Camera
{
public:
    glm::vec3 position;
    glm::vec3 orientation = glm::vec3(0.0f,0.0f,-1.0f);
    glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f);
    glm::mat4 cameraMatrix = glm::mat4(1.0f);

    const int& width;
    const int& height;

    float speed = 0.1f;
    float sensitivity = 100.0f;

    bool mouseHidden = true;

    Camera(const int& width, const int& height, glm::vec3 position);
    void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);
    void Matrix(ProgramShader* shader, const char* uniform);
    void Inputs(GLFWwindow* window);
    void InitScrollCallback(GLFWwindow* window);
};
