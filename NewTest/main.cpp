// NewTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//------- Ignore this ----------
#include<filesystem>
#include <__msvc_filebuf.hpp>

#include "camera.h"
#include "texture.h"
namespace fs = std::filesystem;
//------------------------------

#include <chrono>
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/vec4.hpp>
#include "ebo.h"
#include "shaderClass.h"
#include "shaders.h"
#include "VAO.h"



using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void window_content_scale_callback(GLFWwindow* window, float xScale, float yScale);

void processInput(GLFWwindow* window);
std::string loadShaderSrc(const char* filename);
float zoom = 0.5f;
float lum = 1.0f;
float shuffler[3] = {0.0f,0.0f,0.0f};
Texture* textures[4];
int texIndex = 0;
uint64_t timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
int framesPerSec = 0;
double currentTime = glfwGetTime();

/*float vertices[] = {
    // rectangle             COLORS             TEXTURE MAPPING
    -0.5f, 0.5f, 0.0f,      1.0f, 0.0f,0.0f,     0.0f, 1.0f,// left up
    -0.5f, -0.5f, 0.0f,     0.0f, 0.1f, 0.0f,    0.0f, 0.0f, // left down
    0.5f, 0.5f,0.0f,        0.0f,0.0f,1.0f,      1.0f, 1.0f, // right up
    0.5, -0.5f,0.0f,        0.0f,0.0f,1.0f,      1.0f, 0.0f, // right down
};

GLuint indices[] = {
    0,1,2,
    2,3,1
};*/
// Vertices coordinates
// Vertices coordinates
/*GLfloat vertices[] =
{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
};

// Indices for vertices order
GLuint indices[] =
{
    0, 1, 2, // Bottom side
    0, 2, 3, // Bottom side
    4, 6, 5, // Left side
    7, 9, 8, // Non-facing side
    10, 12, 11, // Right side
    13, 15, 14 // Facing side
};

*/

GLfloat vertices[] =
{
    -1.0f, 0.0f,  1.0f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 1.0f, 0.0f, // face left Bottom side 
    -1.0f, 0.0f,  -1.0f,     0.83f, 0.70f, 0.44f, 	 0.0f, 1.0f,      0.0f, 1.0f, 0.0f, // back left Bottom side
    1.0f, 0.0f,  1.0f,     0.83f, 0.70f, 0.44f, 	 1.0f, 0.0f,      0.0f, 1.0f, 0.0f, // face right Bottom side
    1.0f, 0.0f,  -1.0f,     0.83f, 0.70f, 0.44f, 	 1.0f, 1.0f,      0.0f, 1.0f, 0.0f, // back right Bottom side
};

GLuint indices[] =
{
    0,1,2,
    2,3,1,
};




GLfloat lightVertices[] =
{
    // y     x     z
    -0.1f, -0.1f, 0.1f, //0 face left corner down  
    -0.1f, -0.1f, -0.1f, //1  back left corner down 
    0.1f, -0.1f, -0.1f, //2 back left  cornet up  
    0.1f, -0.1f, 0.1f,  // 3 front left corner up 
    -0.1f, 0.1f, 0.1f, // 4 front right corner down 
    -0.1f, 0.1f, -0.1f, // 5 back right corner down 
    0.1f, 0.1f, -0.1f, // 6 back right corner up
    0.1f, 0.1f, 0.1f // 7 front right corner up
};


GLuint lightIndices[] =
{
    0, 1, 2,
    0, 2, 3, // left
    
    0, 4, 7,
    0, 7, 3, // face
    
    3, 7, 6,
    3, 6, 2, // up
    
    2, 6, 5,
    2, 5, 1, // back
    
    1, 5, 4,
    1, 4, 0, // bottom
    
    4, 5, 6,
    4, 6, 7 // right
}; 

int width = 1280;
int height = 720;
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
    //glfwWindowHint(GLFW_SCALE_TO_MONITOR,GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    

# ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(width,height,"OpenGL testing",NULL,NULL);
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

    glViewport(0,0,width,height);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    glfwSetWindowContentScaleCallback(window, window_content_scale_callback);
    /*
        Shaders
    */

    Shaders shaders = Shaders();
    ProgramShader* defaultShader = shaders.loadShader("assets/vertex_core.glsl","assets/fragment_core.glsl",0);
    ProgramShader* lightShader = shaders.loadShader("assets/vertex_light.glsl","assets/fragment_light.glsl",1);
    cout << "Program POINTER " << defaultShader;
    defaultShader->enableAll();
    lightShader->enableAll();
    //std::string fragment2 = loadShaderSrc("assets/fragment_core.glsl");
    //shader.loadShader(fragment2,GL_FRAGMENT_SHADER,1,1);
    //std::string vertex = loadShaderSrc("assets/vertex_core.glsl");
  //  cout << to_string(shader.getProgram(0).getID()) << endl;
    //shader.loadShader(vertex,GL_VERTEX_SHADER,1,1);
    // ProgramShader green = shader.getProgram(1);
    //shader.getProgram(0).enableAll();
    //shader.getProgram(1).enableAll();

 
    //cout << to_string(shader.getProgram(0).getID()) << endl;
   // cout << to_string(shader.getProgram(1).getID()) << endl;
   /* glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader[0]);
    glDeleteShader(fragmentShader[1]);*/

    
  

    VAO VAO1;
    VAO1.Bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO1(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO EBO1(indices, sizeof(indices));

    // Links VBO to VAO
    VAO1.LinkAttrib(VBO1, 0,3, GL_FLOAT, 11*sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1,3, GL_FLOAT, 11*sizeof(float), (void*)(3*sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2,2, GL_FLOAT, 11*sizeof(float), (void*)(6*sizeof(float)));
    VAO1.LinkAttrib(VBO1, 3,3, GL_FLOAT, 11*sizeof(float), (void*)(8*sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    VAO lightVAO;
    lightVAO.Bind();

    VBO lightVBO(lightVertices,sizeof(lightVertices));
    EBO lightEBO(lightIndices, sizeof(lightIndices));

    lightVAO.LinkAttrib(lightVBO,0,3,GL_FLOAT,3*sizeof(float),(void*)0);

    lightVAO.Unbind();
    lightVBO.Unbind();
    lightEBO.Unbind();

    glm::vec4 lightColor = glm::vec4(1.0f,1.0f,0.0f,1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f,0.5f,0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel,lightPos);

    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel,glm::vec3(0));

    lightShader->use();
    glUniformMatrix4fv(glGetUniformLocation(lightShader->getID(),"model"),1,GL_FALSE,glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader->getID(),"lightColor"),lightColor.x,lightColor.y,lightColor.z,lightColor.w);
    defaultShader->use();
    glUniformMatrix4fv(glGetUniformLocation(defaultShader->getID(),"model"),1,GL_FALSE,glm::value_ptr(pyramidModel));
    glUniform4f(glGetUniformLocation(defaultShader->getID(),"lightColor"),lightColor.x,lightColor.y,lightColor.z,lightColor.w);
    glUniform3f(glGetUniformLocation(defaultShader->getID(),"lightPos"),lightPos.x,lightPos.y,lightPos.z);

    
   // GLuint uniID = glGetUniformLocation(defaultShader->getID(),"scale");
    GLuint uniLum = glGetUniformLocation(defaultShader->getID(),"luminosity");
    GLuint uniShuffler = glGetUniformLocation(defaultShader->getID(),"shuffler");
    

    // Texture
    Texture* plankTexture = new Texture(Texture::AssetsPath(),"planks.png",0);
    Texture* plankSpec = new Texture(Texture::AssetsPath(),"planksSpec.png",GL_TEXTURE_2D,1,GL_RED,GL_UNSIGNED_BYTE);
    Texture* brickTexture = new Texture(Texture::AssetsPath(),"brick.png",0);
    Texture* catTexture = new Texture(Texture::AssetsPath(),"cat.png",0);
    Texture* bgTexture = new Texture(Texture::AssetsPath(),"beaugosse.png",0);

    plankTexture->texUnit(defaultShader,"tex0",0);
    plankSpec->texUnit(defaultShader,"tex1",1);
    brickTexture->texUnit(defaultShader,"tex0",0);
    catTexture->texUnit(defaultShader,"tex0",0);
    bgTexture->texUnit(defaultShader,"tex0",0);
    textures[0] = plankTexture;
    textures[1] = brickTexture;
    textures[2] = catTexture;
    textures[3] = bgTexture;
    // Enables the Depth Buffer
    glEnable(GL_DEPTH_TEST);
    // Variables that help the rotation of the pyramid
    float rotation = 0.0f;
    double prevTime = glfwGetTime();
    Camera camera(width,height,glm::vec3(0.0f,0.0f,2.0f));
    camera.InitScrollCallback(window);
   
    while (!glfwWindowShouldClose(window))
    {
        // read input
        processInput(window);
        camera.Inputs(window);
        //rendering
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw shapes
        //vao1.Bind();
        // Simple timer
        double crntTime = glfwGetTime();
        if (crntTime - prevTime >= 1 / 60)
        {
            rotation += 0.2f;
            prevTime = crntTime;
        }
       
        //glDrawArrays(GL_TRIANGLES,0,6);
        //first triangle
        //glUseProgram(shaderProgram[0]);
    

        
        camera.UpdateMatrix(45.0f,0.01f,100.0f);
        defaultShader->use();
        glUniform3f(glGetUniformLocation(defaultShader->getID(),"camPos"),camera.position.x,camera.position.y,camera.position.z);
        
        camera.Matrix(defaultShader,"camMatrix");
       // glUniform1f(uniID,zoom);


        
        glUniform1f(uniLum,lum);
       
        if(shuffler != NULL)
            glUniform3f(uniShuffler,shuffler[0],shuffler[1],shuffler[2]);

        // make transparency
        Texture::BlendAlphaChannel();
        // bind texture
       // glBindTexture(GL_TEXTURE_2D,texture);
        
        textures[texIndex]->Bind();
       if(texIndex == 0)
       {
           plankSpec->Bind();
       }
        //glUseProgram(shader.getProgram(0).getID());
     
        VAO1.Bind();
        //shader.Activate();
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

        lightShader->use();
        camera.Matrix(lightShader, "camMatrix");
        lightVAO.Bind();
        glDrawElements(GL_TRIANGLES,sizeof(lightIndices)/sizeof(int),GL_UNSIGNED_INT,0);

        ////glUseProgram(shader.getProgram(1).getID());
       // purple.use();
       // glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,(void*) (3*sizeof(unsigned int)));
        // send new frame to window
        glfwSwapBuffers(window);
        glfwPollEvents();

        framesPerSec++;
        //std::cout << timeSinceEpochMillisec() << std::endl;
        if(currentTime+1000 < timeSinceEpochMillisec())
        {
            currentTime = timeSinceEpochMillisec();
            
            std::cout << std::to_string(framesPerSec)+"fps" << std::endl;
            glfwSetWindowTitle(window, ("OpenGL testing | " + std::to_string(framesPerSec)+"fps").c_str());
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

void framebuffer_size_callback(GLFWwindow* window, int _width, int _height)
{
    // resizing
    width = _width;
    height = _height;
    //gluOrtho2D(0.0, width, 0.0, height);
    cout<< "resizing " << width << "&" << height << endl;
 
    glfwGetFramebufferSize(window, &_width, &_height);
    glViewport(0,0,_width,_height);
  //  glfwSetWindowSize(window, width, height);

   
}

void window_content_scale_callback(GLFWwindow* window, float xScale, float yScale)
{
    cout << "Scale X " << xScale << "Scale Y " << yScale << endl;
}

void genShuffle()
{
    shuffler[0] =  static_cast<float>(rand()) / RAND_MAX;
    shuffler[1] =  static_cast<float>(rand()) / RAND_MAX;
    shuffler[2] =  static_cast<float>(rand()) / RAND_MAX;

    cout << shuffler[0] << " " << shuffler[1] << " " << shuffler[2] << endl;
}
bool isPressed = false;

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
        if(glfwGetKey(window,GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            if(!isPressed)
            {
                int getArrayLength = sizeof(textures) / sizeof(*textures);
                cout << getArrayLength << endl;
                if(getArrayLength-1 == texIndex)
                {
                    texIndex = 0;   
                }
                else
                {
                    texIndex++;
                }
                
              
                isPressed = true;
            }
        }
    if(glfwGetKey(window,GLFW_KEY_RIGHT) == GLFW_RELEASE)
    {
        isPressed = false;
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


