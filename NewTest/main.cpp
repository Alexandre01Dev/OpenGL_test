// NewTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <chrono>
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#include "shader.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
std::string loadShaderSrc(const char* filename);

uint64_t timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
int framesPerSec = 0;
uint64_t start = timeSinceEpochMillisec();
int main()
{
    std::cout << "Hello, World" << std::endl;

    int success;
    char infoLog[512];


    /* glm test 
    glm::vec4 vec(1.0f,0.0f,1.0f,1.0f);     //base vector
    glm::mat4 trans = glm::mat4(1.0f); // identity matrix
    // translate the vector with (1,1,0)
   // trans = glm::translate(trans,glm::vec3(1.0f,1.0f,0.0f));
   // trans = glm::rotate(trans,glm::radians(90.0f),glm::vec3(0.0,0.0,1.0)); //rotate
    trans = glm::scale(trans, glm::vec3(0.5,0.5,0.5)); // scaling
    vec = trans * vec;
    std::cout << vec.x << ' ' << vec.y << ' ' << vec.z << std::endl;
    */

    
    
    
    
    glfwInit();

    // openGL version 3.4
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);

    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

# ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE)
#endif

    GLFWwindow* window = glfwCreateWindow(800,600,"OpenGL testing",NULL,NULL);

    if(window == NULL)
    {
        std::cout << "Could not create a window on your system." << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0,0,800,600);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    /*
        Shaders
    */

    Shader shader = Shader("assets/vertex_core.glsl","assets/fragment_core.glsl");
    ProgramShader purple = shader.getProgram(0);
    std::string fragment2 = loadShaderSrc("assets/fragment_core2.glsl");
    shader.loadShader(fragment2,GL_FRAGMENT_SHADER,1,1);
    std::string vertex = loadShaderSrc("assets/vertex_core.glsl");
    cout << to_string(shader.getProgram(0).getID()) << endl;
    shader.loadShader(vertex,GL_VERTEX_SHADER,1,1);
    ProgramShader green = shader.getProgram(1);
    shader.getProgram(0).enableAll();
    shader.getProgram(1).enableAll();
    

    cout << to_string(shader.getProgram(0).getID()) << endl;
    cout << to_string(shader.getProgram(1).getID()) << endl;
   /* glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader[0]);
    glDeleteShader(fragmentShader[1]);*/

    

    //vertex array
    // float vertices[] = {
    //     0.5f, 0.5f , 0.0f, // top right
    //     -0.5f, 0.5f, 0.0f, // top left
    //     -0.5f, -0.5f, 0.0f, // bottom left
    //     0.5f, -0.5f,0.0f, // bottom right
    // };
    // unsigned int indices[] = {
    //     0,1,2, // first triangle
    //     2,3,0
    // };

    float vertices[] = {
        // first triangle
        -0.5f, -0.5f, 0.0f,
        -0.25f, 0.5f, 0.0f,
        -0.1f, -0.15f, 0.0f,

        // second triangle
        0.5f, -0.5f, 0.0f,
        0.25f, 0.5f, 0.0f,
        0.1f, -0.5f, 0.0f
    };

    unsigned int indices[] = {
        0,1,2,
        3,4,5
    };

    // VAO (Vertex Array Object) VBO (Vertex Buffer Object)
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);

    // bind VAO
    glBindVertexArray(VAO);

    // bind VBO
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices , GL_STATIC_DRAW);

    
    // set attribute pointer
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    // set up EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    while (!glfwWindowShouldClose(window))
    {
        // read input
        processInput(window);
        //rendering
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw shapes
        glBindVertexArray(VAO);
       
        //glDrawArrays(GL_TRIANGLES,0,6);
        //first triangle
        //glUseProgram(shaderProgram[0]);
        green.use();
        //glUseProgram(shader.getProgram(0).getID());
        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,0);

        //glUseProgram(shader.getProgram(1).getID());
        purple.use();
        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,(void*) (3*sizeof(unsigned int)));
        // send new frame to window
        glfwSwapBuffers(window);
        glfwPollEvents();

        framesPerSec++;
        //std::cout << timeSinceEpochMillisec() << std::endl;
        if(start+1000 < timeSinceEpochMillisec())
        {
            start = timeSinceEpochMillisec();
            std::cout << std::to_string(framesPerSec)+"fps" << std::endl;
            framesPerSec = 0;
        }
    }
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VAO);
    glDeleteBuffers(1,&EBO);
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // resizing
    glViewport(0,0,width,height);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window,true);
    }   
}

std::string loadShaderSrc(const char* filename)
{
    std::ifstream file;
    std::stringstream buf;

    std::string ret = "";

    file.open(filename);

    if(file.is_open())
    {
        buf << file.rdbuf();
        ret = buf.str();
    }else
    {
        std::cout << "Could not open " << filename << std::endl;
    }
    return ret;
}

