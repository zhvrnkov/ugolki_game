#ifndef renderer_h
#define renderer_h

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "shader.h"
#include "mesh.h"
#include <vector>
#include "camera/camera.h"

#define SCR_WIDTH 960.0
#define SCR_HEIGHT 960.0
#define UNIT_SIZE 0.025f

using namespace glm;
using namespace std;

typedef struct {
} RenderingContext;

struct Renderer {
  public:
  Program mainProgram;
  Mesh boardMesh;
  Mesh cubeMesh;
  Camera camera;
  mat4 projection;
  RenderingContext context;
};

typedef struct {
  void (*mouseButtonCallback)(double, double);
  void (*scrollCallback)(double, double);
  void (*keyCallback)(int, int, int, int);
} WindowPresenter;

static vector<Vertex> boardVertices {
  { .Position = vec3(-1.0f, -1.0f, 0.0f), .Normal = vec3(0.0f, 0.0f, 1.0f) },
  { .Position = vec3(1.0f, -1.0f, 0.0f),  .Normal = vec3(0.0f, 0.0f, 1.0f) },
  { .Position = vec3(1.0f,  1.0f, 0.0f),  .Normal = vec3(0.0f, 0.0f, 1.0f) },
  { .Position = vec3(1.0f,  1.0f, 0.0f),  .Normal = vec3(0.0f, 0.0f, 1.0f) },
  { .Position = vec3(-1.0f,  1.0f, 0.0f), .Normal = vec3(0.0f, 0.0f, 1.0f) },
  { .Position = vec3(-1.0f, -1.0f, 0.0f), .Normal = vec3(0.0f, 0.0f, 1.0f) },
};

static vector<Vertex> cubeVertices {
  // positions          // normals           // texture coords
  { .Position = vec3(-0.5f, -0.5f, -0.5f), .Normal = vec3( 0.0f,  0.0f, -1.0f) },
  { .Position = vec3(0.5f, -0.5f, -0.5f), .Normal = vec3( 0.0f,  0.0f, -1.0f) },
  { .Position = vec3(0.5f,  0.5f, -0.5f), .Normal = vec3( 0.0f,  0.0f, -1.0f) },
  { .Position = vec3(0.5f,  0.5f, -0.5f), .Normal = vec3( 0.0f,  0.0f, -1.0f) },
  { .Position = vec3(-0.5f,  0.5f, -0.5f), .Normal = vec3( 0.0f,  0.0f, -1.0f) },
  { .Position = vec3(-0.5f, -0.5f, -0.5f), .Normal = vec3( 0.0f,  0.0f, -1.0f) },

  // { .Position = vec3(-0.5f, -0.5f,  0.5f), .Normal = vec3( 0.0f,  0.0f,  1.0f) },
  // { .Position = vec3(0.5f, -0.5f,  0.5f), .Normal = vec3( 0.0f,  0.0f,  1.0f) },
  // { .Position = vec3(0.5f,  0.5f,  0.5f), .Normal = vec3( 0.0f,  0.0f,  1.0f) },
  // { .Position = vec3(0.5f,  0.5f,  0.5f), .Normal = vec3( 0.0f,  0.0f,  1.0f) },
  // { .Position = vec3(-0.5f,  0.5f,  0.5f), .Normal = vec3( 0.0f,  0.0f,  1.0f) },
  // { .Position = vec3(-0.5f, -0.5f,  0.5f), .Normal = vec3( 0.0f,  0.0f,  1.0f) },

  // { .Position = vec3(-0.5f,  0.5f,  0.5f), .Normal = vec3(-1.0f,  0.0f,  0.0f) },
  // { .Position = vec3(-0.5f,  0.5f, -0.5f), .Normal = vec3(-1.0f,  0.0f,  0.0f) },
  // { .Position = vec3(-0.5f, -0.5f, -0.5f), .Normal = vec3(-1.0f,  0.0f,  0.0f) },
  // { .Position = vec3(-0.5f, -0.5f, -0.5f), .Normal = vec3(-1.0f,  0.0f,  0.0f) },
  // { .Position = vec3(-0.5f, -0.5f,  0.5f), .Normal = vec3(-1.0f,  0.0f,  0.0f) },
  // { .Position = vec3(-0.5f,  0.5f,  0.5f), .Normal = vec3(-1.0f,  0.0f,  0.0f) },

  // { .Position = vec3(0.5f,  0.5f,  0.5f), .Normal = vec3( 1.0f,  0.0f,  0.0f) },
  // { .Position = vec3(0.5f,  0.5f, -0.5f), .Normal = vec3( 1.0f,  0.0f,  0.0f) },
  // { .Position = vec3(0.5f, -0.5f, -0.5f), .Normal = vec3( 1.0f,  0.0f,  0.0f) },
  // { .Position = vec3(0.5f, -0.5f, -0.5f), .Normal = vec3( 1.0f,  0.0f,  0.0f) },
  // { .Position = vec3(0.5f, -0.5f,  0.5f), .Normal = vec3( 1.0f,  0.0f,  0.0f) },
  // { .Position = vec3(0.5f,  0.5f,  0.5f), .Normal = vec3( 1.0f,  0.0f,  0.0f) },

  // { .Position = vec3(-0.5f, -0.5f, -0.5f), .Normal = vec3( 0.0f, -1.0f,  0.0f) },
  // { .Position = vec3(0.5f, -0.5f, -0.5f), .Normal = vec3( 0.0f, -1.0f,  0.0f) },
  // { .Position = vec3(0.5f, -0.5f,  0.5f), .Normal = vec3( 0.0f, -1.0f,  0.0f) },
  // { .Position = vec3(0.5f, -0.5f,  0.5f), .Normal = vec3( 0.0f, -1.0f,  0.0f) },
  // { .Position = vec3(-0.5f, -0.5f,  0.5f), .Normal = vec3( 0.0f, -1.0f,  0.0f) },
  // { .Position = vec3(-0.5f, -0.5f, -0.5f), .Normal = vec3( 0.0f, -1.0f,  0.0f) },

  // { .Position = vec3(-0.5f,  0.5f, -0.5f), .Normal = vec3( 0.0f,  1.0f,  0.0f) },
  // { .Position = vec3(0.5f,  0.5f, -0.5f), .Normal = vec3( 0.0f,  1.0f,  0.0f) },
  // { .Position = vec3(0.5f,  0.5f,  0.5f), .Normal = vec3( 0.0f,  1.0f,  0.0f) },
  // { .Position = vec3(0.5f,  0.5f,  0.5f), .Normal = vec3( 0.0f,  1.0f,  0.0f) },
  // { .Position = vec3(-0.5f,  0.5f,  0.5f), .Normal = vec3( 0.0f,  1.0f,  0.0f) },
  // { .Position = vec3(-0.5f,  0.5f, -0.5f), .Normal = vec3( 0.0f,  1.0f,  0.0f) },
};

WindowPresenter windowPresenter;
GLFWwindow *window;

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
  if (windowPresenter.scrollCallback != NULL) {
    windowPresenter.scrollCallback(xoffset, yoffset);
  }
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
  if((button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) == false)
    return;
  double x, y;
  glfwGetCursorPos(window, &x, &y);
  if (windowPresenter.mouseButtonCallback != NULL) {
    windowPresenter.mouseButtonCallback((x / (SCR_WIDTH / 2.0)) - 1.0,
                                        1.0 - (y / (SCR_HEIGHT / 2.0)));
  }
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (windowPresenter.keyCallback != NULL) {
    windowPresenter.keyCallback(key, scancode, action, mods);
  }
}

void setupWindow() {
  glfwInit();

	glfwWindowHint(GLFW_SAMPLES, 256);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,"Tutorial 02 - Red triangle", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewExperimental = 1;
  glewInit();
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_BLEND );

  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetKeyCallback(window, keyCallback);

	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
}

Renderer makeRenderer() {
  Program mainProgram = Program("./renderer/shaders/main.vert", "./renderer/shaders/main.frag");
//  Program peaceProgram = Program("./renderer/shaders/main.vert", "./renderer/shaders/main.frag");
  RenderingContext context;
  Renderer output = {
    .mainProgram = mainProgram,
    .boardMesh = Mesh(boardVertices),
    .cubeMesh = Mesh(cubeVertices),
    .camera = Camera(),
    .projection = make_projection_angle(45.0, 1, 0.1, 100),
    .context = context
  };
  return output;
}

vec3 translations[] = {
  vec3( 0.0f,  0.0f,  0.0f),
  vec3( 2.0f,  5.0f, -15.0f),
  vec3(-1.5f, -2.2f, -2.5f),
  vec3(-3.8f, -2.0f, -12.3f),
  vec3 (2.4f, -0.4f, -3.5f),
  vec3(-1.7f,  3.0f, -7.5f),
  vec3( 1.3f, -2.0f, -2.5f),
  vec3( 1.5f,  2.0f, -2.5f),
  vec3( 1.5f,  0.2f, -1.5f),
  vec3(-1.3f,  1.0f, -1.5f)
};

vec3 rotationVectors[] = {
  vec3(1.0, 0.0, 0.0),
  vec3(1.0, 0.3, 0.5),
  vec3(1.0, 0.3, 0.5),
  vec3(1.0, 0.3, 0.5),
  vec3(1.0, 0.3, 0.5),
  vec3(1.0, 0.3, 0.5),
  vec3(1.0, 0.3, 0.5),
  vec3(1.0, 0.3, 0.5),
  vec3(1.0, 0.3, 0.5),
  vec3(1.0, 0.3, 0.5),
};

void render(Renderer &renderer) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  renderer.mainProgram.setMat4("model", make_model(translations[0], rotationVectors[0], M_PI / 2));
  renderer.mainProgram.setMat4("view", renderer.camera.viewMatrix());
  renderer.mainProgram.setMat4("projection", renderer.projection);

  renderer.boardMesh.Draw(renderer.mainProgram);

  glfwSwapBuffers(window);
  glfwPollEvents();
}

bool should_close() {
  return glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && 
    glfwWindowShouldClose(window) == 0;
}

#endif
