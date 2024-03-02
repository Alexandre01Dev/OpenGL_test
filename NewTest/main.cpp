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

#include "EBO.h"
#include "shaderClass.h"
#include "shaders.h"
#include "VAO.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
std::string loadShaderSrc(const char* filename);
float zoom = 0.5f;
float lum = 1.0f;
float shuffler[3] = {0.0f,0.0f,0.0f};
uint64_t timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
int framesPerSec = 0;
uint64_t start = timeSinceEpochMillisec();
int main()
{
    std::cout << "Hello, World" << std::endl;
    

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

    Shaders shaders = Shaders("assets/vertex_core.glsl","assets/fragment_core.glsl");
    ProgramShader* purple = shaders.getProgram(0);
    cout << "Program POINTER " << purple;
    purple->enableAll();
    //std::string fragment2 = loadShaderSrc("assets/fragment_core.glsl");
    //shader.loadShader(fragment2,GL_FRAGMENT_SHADER,1,1);
    //std::string vertex = loadShaderSrc("assets/vertex_core.glsl");
  //  cout << to_string(shader.getProgram(0).getID()) << endl;
    //shader.loadShader(vertex,GL_VERTEX_SHADER,1,1);
    // ProgramShader green = shader.getProgram(1);
    //shader.getProgram(0).enableAll();
    //shader.getProgram(1).enableAll();
    
    Shader shader = Shader("assets/vertex_core.glsl","assets/fragment_core.glsl");
    //cout << to_string(shader.getProgram(0).getID()) << endl;
   // cout << to_string(shader.getProgram(1).getID()) << endl;
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
        -0.5f, -0.5f, 0.0f,  0.0f, 0.4f, 0.0f, //left bottom
        -0.25f, 0.5f, 0.0f,  0.5f, 0.0f, 0.0f,  // top
        -0.1f, -0.15f, 0.0f,  0.0f, 0.0f, 0.5f, // right bottom

        // second triangle
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left bottom
        0.25f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // top
        0.1f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right bottom
    };

    GLuint indices[] = {
        0,1,2,
        3,4,5
    };

    VAO VAO1;
    VAO1.Bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO1(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO EBO1(indices, sizeof(indices));

    // Links VBO to VAO
    VAO1.LinkAttrib(VBO1, 0,3, GL_FLOAT, 6*sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1,3, GL_FLOAT, 6*sizeof(float), (void*)(3*sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    cout << purple->getID() << " change scale" << endl;
    GLuint uniID = glGetUniformLocation(purple->getID(),"scale");
    GLuint uniLum = glGetUniformLocation(purple->getID(),"luminosity");
    GLuint uniShuffler = glGetUniformLocation(purple->getID(),"shuffler");
    


    while (!glfwWindowShouldClose(window))
    {
        // read input
        processInput(window);
        //rendering
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw shapes
        //vao1.Bind();
   
       
        //glDrawArrays(GL_TRIANGLES,0,6);
        //first triangle
        //glUseProgram(shaderProgram[0]);
        purple->use();
        glUniform1f(uniID,zoom);
        glUniform1f(uniLum,lum);
        if(shuffler != NULL)
            glUniform3f(uniShuffler,shuffler[0],shuffler[1],shuffler[2]);
        //glUseProgram(shader.getProgram(0).getID());
     
        VAO1.Bind();
        //shader.Activate();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        ////glUseProgram(shader.getProgram(1).getID());
       // purple.use();
       // glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,(void*) (3*sizeof(unsigned int)));
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
    // delete all
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    //shader.Delete();
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // resizing
    glViewport(0,0,width,height);
}

void genShuffle()
{
    shuffler[0] =  static_cast<float>(rand()) / RAND_MAX;
    shuffler[1] =  static_cast<float>(rand()) / RAND_MAX;
    shuffler[2] =  static_cast<float>(rand()) / RAND_MAX;

    cout << shuffler[0] << " " << shuffler[1] << " " << shuffler[2] << endl;
}
void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window,true);
    }
    if(glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS)
    {
        std::cout << "Zoom to " << zoom << endl;
        if(zoom < 1)
            zoom += 0.05f;
    }
    if(glfwGetKey(window,GLFW_KEY_DOWN) == GLFW_PRESS)
    {
     
        if(zoom > -0.9)
        {
            zoom -= 0.05f;
        }
    }
    if(glfwGetKey(window,GLFW_KEY_L) == GLFW_PRESS)
    {
        
        lum += 0.05f;
    }

    if(glfwGetKey(window,GLFW_KEY_K) == GLFW_PRESS)
    {
        
        lum -= 0.05f;
    }
    if(glfwGetKey(window,GLFW_KEY_R) == GLFW_PRESS)
    {
        
        genShuffle();
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
       cout << "Could not open " << filename << endl;
    }
    return ret;
}

