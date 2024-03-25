#include "camera.h"

#include <iostream>

int mouseState = 0;
float speedWheel = 1;


Camera::Camera(const int& width, const int& height, glm::vec3 position): position(position), width(width),height(height)
{
}

void Camera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(position, position+orientation, up);
    projection = glm::perspective(glm::radians(FOVdeg), (float) width/height, nearPlane, farPlane);
    cameraMatrix = projection*view;
}

void Camera::Matrix(ProgramShader* shader, const char* uniform)
{
    glUniformMatrix4fv(glGetUniformLocation(shader->getID(),uniform),1,GL_FALSE,glm::value_ptr(cameraMatrix));
}

void Camera::Inputs(GLFWwindow* window)
{
    if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
    {
        position += speed * orientation;
    }
    if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
    {
        position += speed * -glm::normalize(glm::cross(orientation,up));
    }
    if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS)
    {
        position += speed * -orientation;
    }
    if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)
    {
        position += speed * glm::normalize(glm::cross(orientation,up));
    }
    if(glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        position += speed * up;
    }
    if(glfwGetKey(window,GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        position += speed * -up;
    }
    if(glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        speed = 0.4f*speedWheel;
    }else if(glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE){
        speed = 0.1f*speedWheel;
    }
    
    if(glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
    {
        if(mouseState == -1) return;
        if(mouseState == 2)
        {
            mouseState = -1;
            std::cout << "Reset mouse 1" << std::endl;
            glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
            mouseHidden = false;
            return;
        }
        mouseState = 1;
    } if(glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE){
        if(mouseState == 1)
        {
            mouseState = 2;
        }
        if(mouseState == -1)
        {
            std::cout << "Reset mouse 2" << std::endl;
            mouseState = 0;
        }
        //glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
    }

    if(mouseState > 0)
    {
        glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_HIDDEN);
        mouseHidden = true;

        double mouseX;
        double mouseY;
        glfwGetCursorPos(window,&mouseX,&mouseY);

        float rotx = sensitivity * (float)(mouseY - (height / 2)) / height;
        float roty = sensitivity * (float)(mouseX - (width / 2)) / width;

        glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotx), glm::normalize(glm::cross(orientation, up)));

        if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
        {
            orientation = newOrientation;
        }
        orientation = glm::rotate(orientation , glm::radians(-roty),up);
        glfwSetCursorPos(window, (float)width/2,(float)height/2);
    }

    
    
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
   if(mouseState > 0)
   {
       if(yoffset == 1)
       {
           speedWheel = glm::max(speedWheel+0.03f,0.0f);
       }else
       {
           if(yoffset == -1)
           {
               speedWheel = glm::max(speedWheel-0.03f,0.0f);
           }
       }
 
   } 
}
void Camera::InitScrollCallback(GLFWwindow* window)
{
    glfwSetScrollCallback(window,scroll_callback);
}
