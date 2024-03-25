// NewTest.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//
//------- Ignore this ----------
#include <filesystem>

#include "camera.h"
#include "glfw/src/internal.h"
#include "light.h"
#include "texture.h"

namespace fs = std::filesystem;
//------------------------------

#include <GLFW/glfw3.h>
#include <chrono>
#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <array>
#include <list>

#include "mesh.h"
#include "shaders.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void window_content_scale_callback(GLFWwindow *window, float xScale,
                                   float yScale);

void processInput(GLFWwindow *window);
std::string loadShaderSrc(const char *filename);
float zoom = 0.5f;
float lum = 1.0f;
float shuffler[3] = {0.0f, 0.0f, 0.0f};

int texIndex = 0;
uint64_t timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch())
      .count();
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
{ //     COORDINATES     /        COLORS          /    TexCoord   / NORMALS //
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f,
-1.0f, 0.0f, // Bottom side -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,
0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side 0.5f, 0.0f, -0.5f,     0.83f,
0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side 0.5f, 0.0f,
0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom
side

    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f,
0.5f,  0.0f, // Left Side -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f,
0.0f,     -0.8f, 0.5f,  0.0f, // Left Side 0.0f, 0.8f,  0.0f,     0.92f, 0.86f,
0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f,
0.5f, -0.8f, // Non-facing side 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,
0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side 0.0f, 0.8f,  0.0f, 0.92f,
0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f,
0.5f,  0.0f, // Right side 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f,
0.0f,      0.8f, 0.5f,  0.0f, // Right side 0.0f, 0.8f,  0.0f,     0.92f, 0.86f,
0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f,
0.5f,  0.8f, // Facing side -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,
0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side 0.0f, 0.8f,  0.0f,     0.92f,
0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
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

Vertex vertices[] = {
    //     COORDINATES     /        COLORS          /    TexCoord   / NORMALS //
    Vertex{glm::vec3(-100.0f, 0.0f, 100.0f), glm::vec3(0.0f, 1.0f, 0.0f),
           glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(-100.0f, 0.0f, -100.0f), glm::vec3(0.0f, 1.0f, 0.0f),
           glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 100.0f)},
    Vertex{glm::vec3(100.0f, 0.0f, 100.0f), glm::vec3(0.0f, 1.0f, 0.0f),
           glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(100.0f, 0.0f)},
    Vertex{glm::vec3(100.0f, 0.0f, -100.0f), glm::vec3(0.0f, 1.0f, 0.0f),
           glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(100.0f, 100.0f)},
};

GLuint indices[] = {
    0, 1, 2, 2, 3, 1,
};

Vertex lightVertices[] = {
    // y     x     z
    Vertex{glm::vec3(-0.1f, -0.1f, 0.1f)},  // 0 face left corner down
    Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)}, // 1  back left corner down
    Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},  // 2 back left  cornet up
    Vertex{glm::vec3(0.1f, -0.1f, 0.1f)},   // 3 front left corner up
    Vertex{glm::vec3(-0.1f, 0.1f, 0.1f)},   // 4 front right corner down
    Vertex{glm::vec3(-0.1f, 0.1f, -0.1f)},  // 5 back right corner down
    Vertex{glm::vec3(0.1f, 0.1f, -0.1f)},   // 6 back right corner up
    Vertex{glm::vec3(0.1f, 0.1f, 0.1f)}     // 7 front right corner up
};

GLuint lightIndices[] = {
    0, 1, 2, 0, 2, 3, // left

    0, 4, 7, 0, 7, 3, // face

    3, 7, 6, 3, 6, 2, // up

    2, 6, 5, 2, 5, 1, // back

    1, 5, 4, 1, 4, 0, // bottom

    4, 5, 6, 4, 6, 7 // right
};

int width = 1280;
int height = 720;
unsigned int samples = 8;

int main() {
  // Création d'une nouvelle console
  AllocConsole();
  FILE *fp;
  freopen_s(&fp, "CONOUT$", "w", stdout);
  cout << "Hello, World" << endl;
  /* glm test
  glm::vec4 vec(1.0f,0.0f,1.0f,1.0f);     //base vector
  glm::mat4 trans = glm::mat4(1.0f); // identity matrix
  // translate the vector with (1,1,0)
 // trans = glm::translate(trans,glm::vec3(1.0f,1.0f,0.0f));
 // trans = glm::rotate(trans,glm::radians(90.0f),glm::vec3(0.0,0.0,1.0));
 //rotate trans = glm::scale(trans, glm::vec3(0.5,0.5,0.5)); // scaling vec =
 trans * vec; std::cout << vec.x << ' ' << vec.y << ' ' << vec.z << std::endl;
  */

  glfwInit();

  // openGL version 3.4
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GL_SAMPLES, samples);
  glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_FALSE);
  cout << "APPLE COCOA DETECTED !" << endl;
#endif

  GLFWwindow *window =
      glfwCreateWindow(width, height, "OpenGL testing", NULL, NULL);
  if (window == NULL) {
    std::cout << "Could not create a window on your system." << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress))) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    glfwTerminate();
    return -1;
  }

  glViewport(0, 0, width, height);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetWindowContentScaleCallback(window, window_content_scale_callback);
  /*
      Shaders
  */
  Texture textures[]{
      Texture(Texture::AssetsPath(), "planks.png", 0, TexType::DIFFUSE),
      Texture(Texture::AssetsPath(), "planksSpec.png", TexType::SPECULAR, 1,
              GL_RED, GL_UNSIGNED_BYTE)};

  Shaders shaders = Shaders();
  ProgramShader *defaultShader = shaders.loadShader(
      "assets/vertex_core.glsl", "assets/fragment_core.glsl", 0);
  ProgramShader *lightShader = shaders.loadShader(
      "assets/vertex_light.glsl", "assets/fragment_light.glsl", 1);

  defaultShader->enableAll();
  lightShader->enableAll();
  // std::string fragment2 = loadShaderSrc("assets/fragment_core.glsl");
  // shader.loadShader(fragment2,GL_FRAGMENT_SHADER,1,1);
  // std::string vertex = loadShaderSrc("assets/vertex_core.glsl");
  //  cout << to_string(shader.getProgram(0).getID()) << endl;
  // shader.loadShader(vertex,GL_VERTEX_SHADER,1,1);
  // ProgramShader green = shader.getProgram(1);
  // shader.getProgram(0).enableAll();
  // shader.getProgram(1).enableAll();

  // cout << to_string(shader.getProgram(0).getID()) << endl;
  // cout << to_string(shader.getProgram(1).getID()) << endl;
  /* glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader[0]);
   glDeleteShader(fragmentShader[1]);*/
  std::vector<Vertex> verts(vertices,
                            vertices + sizeof(vertices) / sizeof(Vertex));
  std::vector<GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
  std::vector<Texture> tex(textures,
                           textures + sizeof(textures) / sizeof(Texture));
  // Create floor mesh
  Mesh floor(verts, ind, tex);

  std::vector<Vertex> lightVerts(
      lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
  std::vector<GLuint> lightInd(
      lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
  Mesh light(lightVerts, lightInd, tex);

  glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
  glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
  glm::mat4 lightModel = glm::mat4(1.0f);
  lightModel = glm::translate(lightModel, lightPos);

  glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::mat4 objectModel = glm::mat4(1.0f);
  objectModel = glm::translate(objectModel, objectPos);

  lightShader->use();
  glUniformMatrix4fv(glGetUniformLocation(lightShader->getID(), "model"), 1,
                     GL_FALSE, glm::value_ptr(lightModel));
  glUniform4f(glGetUniformLocation(lightShader->getID(), "lightColor"),
              lightColor.x, lightColor.y, lightColor.z, lightColor.w);

  defaultShader->use();
  glUniformMatrix4fv(glGetUniformLocation(defaultShader->getID(), "model"), 1,
                     GL_FALSE, glm::value_ptr(objectModel));
  glUniform4f(glGetUniformLocation(defaultShader->getID(), "lightColor"),
              lightColor.x, lightColor.y, lightColor.z, lightColor.w);
  glUniform3f(glGetUniformLocation(defaultShader->getID(), "lightPos"),
              lightPos.x, lightPos.y, lightPos.z);

  // directional light
  defaultShader->setVec3("directLight.color", glm::vec3(1.0f, 1.0f, 1.0f));
  defaultShader->setFloat("directLight.ambient", 0.2f);
  defaultShader->setFloat("directLight.diffuse", 0.4f);
  defaultShader->setFloat("directLight.specular", 0.03f);
  defaultShader->setInt("hasDirectLight", 1);
  // points light
  Light light1(glm::vec3(lightPos), Light::SPECULAR,
               glm::vec3(1.0f, 1.0f, 1.0f), 0.2f, 5.0f, 0.25f);
  light1.SetupShader(defaultShader);
  Light light2(glm::vec3(glm::vec3(-80.5f, 0.5f, 0.5f)), Light::SPECULAR,
               glm::vec3(1.0f, 0.5f, 0.5f), 0.2f, 5.0f, 0.25f);
  light2.SetupShader(defaultShader);

  // GLuint uniID = glGetUniformLocation(defaultShader->getID(),"scale");
  GLuint uniLum = glGetUniformLocation(defaultShader->getID(), "luminosity");
  GLuint uniShuffler = glGetUniformLocation(defaultShader->getID(), "shuffler");

  // Texture
  // Enables the Depth Buffer
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_MULTISAMPLE);
  // Variables that help the rotation of the pyramid
  float rotation = 0.0f;
  double prevTime = glfwGetTime();
  double prevTime2 = glfwGetTime();
  Camera camera(width, height, glm::vec3(0.0f, 5.0f, 2.0f));
  camera.InitScrollCallback(window);
  glfwSwapInterval(0.0f);
  // make transparency
  Texture::BlendAlphaChannel();
  bool revert = false;

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window,true);
  ImGui_ImplOpenGL3_Init("#version 330");
  std::array<float, 3> lColor = {1.0f, 0.0f, 0.0f}; // Reference to the array variable
  std::list<Light> lights = {};
  auto cLength = *lColor.data();
  while (!glfwWindowShouldClose(window)) {
    // read input
    processInput(window);
    camera.Inputs(window);
    // rendering
    glClearColor(0.2f, 0.3f, 0.3f, 0.4f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    // draw shapes
    // vao1.Bind();
    // Simple timer
    double crntTime = glfwGetTime();
    if (crntTime - prevTime >= 1 / 60) {
      rotation += 0.2f;
      //   cout << "Move" << endl;
   //   cout << abs(light1.pos.x) << endl;

      if (light1.pos.x < 40 && !revert) {
        light1.pos.x += 0.1f;
        light1.pos.z += 0.1f;
      } else {
        // cout << "check" << endl;
        revert = true;
        if (light1.pos.x < -40) {

          revert = false;
        }
        light1.pos.x -= 0.1f;
        light1.pos.z -= 0.1f;
      }
      // creation of a new light randomly in map

      /* Light
       n_light(glm::vec3(lightPos),Light::SPECULAR,glm::vec3(1.0f,1.0f,1.0f),0.2f,5.0f,0.25f);
       n_light.SetupShader(defaultShader);*/
      light1.SetupShader(defaultShader);
      prevTime = crntTime;
      // light1.SetupShader(defaultShader);
    }

    if (crntTime - prevTime2 >= 0.1f) {
      if (Light::getStaticID() < 128) {
        Light rLight(light1.pos, Light::SPECULAR, lColor,
                     0.0f, 1.0f, 0.25f);
        rLight.SetupShader(defaultShader);
        lights.push_back(rLight);
      }
      prevTime2 = crntTime;
    }
    // glDrawArrays(GL_TRIANGLES,0,6);
    // first triangle
    // glUseProgram(shaderProgram[0]);

    camera.UpdateMatrix(45.0f, 0.01f, 5000.0f);
    // glUniform1f(uniID,zoom);

    // bind texture

    light.Draw(lightShader, camera);
    floor.Draw(defaultShader, camera);

    // IMGUI

    ImGui::Begin("Test IMGUI window");
    ImGui::Text("Hello !");

    ImGui::ColorEdit3("Color",lColor.data());
    if(cLength != *lColor.data()){
        cout << "Modified" << endl;
        for ( Light light: lights) {
            light.SetupShader(defaultShader);
        }
        cLength = *lColor.data();
    }
    ImGui::End();

    ImGui::Render();
    if(camera.mouseHidden){
        ImGui::SetMouseCursor(ImGuiMouseCursor_None);
    }
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // send new frame to window
    glfwSwapBuffers(window);
    glfwPollEvents();

    framesPerSec++;
    // std::cout << timeSinceEpochMillisec() << std::endl;
    if (currentTime + 1000 < timeSinceEpochMillisec()) {
      currentTime = timeSinceEpochMillisec();

      std::cout << std::to_string(framesPerSec) + "fps" << std::endl;
      glfwSetWindowTitle(window,
                         ("OpenGL testing | " + std::to_string(framesPerSec) +
                          "fps | " + std::to_string(width) + "x" +
                          std::to_string(height))
                             .c_str());
      framesPerSec = 0;
    }
  }

  ImGui_ImplGlfw_Shutdown();
  ImGui_ImplOpenGL3_Shutdown();
  ImGui::DestroyContext();
  defaultShader->removeAll();
  lightShader->removeAll();
  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int _width, int _height) {
  // resizing
  width = _width;
  height = _height;
  // gluOrtho2D(0.0, width, 0.0, height);
  cout << "resizing " << width << "&" << height << endl;

  glfwGetFramebufferSize(window, &_width, &_height);
  glViewport(0, 0, _width, _height);
  //  glfwSetWindowSize(window, width, height);
}

void window_content_scale_callback(GLFWwindow *window, float xScale,
                                   float yScale) {
  cout << "Scale X " << xScale << "Scale Y " << yScale << endl;
}

void genShuffle() {
  shuffler[0] = static_cast<float>(rand()) / RAND_MAX;
  shuffler[1] = static_cast<float>(rand()) / RAND_MAX;
  shuffler[2] = static_cast<float>(rand()) / RAND_MAX;

  cout << shuffler[0] << " " << shuffler[1] << " " << shuffler[2] << endl;
}

void processInput(GLFWwindow *window) {

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
    std::cout << "Zoom to " << zoom << endl;
    if (zoom < 1)
      zoom += 0.05f;
  }
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {

    if (zoom > -0.9) {
      zoom -= 0.05f;
    }
  }

  if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {

    lum += 0.05f;
  }

  if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {

    lum -= 0.05f;
  }
  if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {

    genShuffle();
  }
}
