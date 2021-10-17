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
#include "../game.h"

#define SCR_WIDTH 960.0
#define SCR_HEIGHT 960.0
#define UNIT_SIZE 0.025f

using namespace glm;
using namespace std;

struct Renderer {
public:
  Program boardProgram;
  Program peaceProgram;
  Mesh boardMesh;
  Mesh cubeMesh;
  Camera camera;
  mat4 projection;
  float time;
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
  { .Position = vec3(-1.0f, -1.0f, -1.0f), .Normal = vec3( 0.0f,  0.0f, -1.0f) },
  { .Position = vec3(1.0f, -1.0f, -1.0f), .Normal = vec3( 0.0f,  0.0f, -1.0f) },
  { .Position = vec3(1.0f,  1.0f, -1.0f), .Normal = vec3( 0.0f,  0.0f, -1.0f) },
  { .Position = vec3(1.0f,  1.0f, -1.0f), .Normal = vec3( 0.0f,  0.0f, -1.0f) },
  { .Position = vec3(-1.0f,  1.0f, -1.0f), .Normal = vec3( 0.0f,  0.0f, -1.0f) },
  { .Position = vec3(-1.0f, -1.0f, -1.0f), .Normal = vec3( 0.0f,  0.0f, -1.0f) },

  { .Position = vec3(-1.0f, -1.0f,  1.0f), .Normal = vec3( 0.0f,  0.0f,  1.0f) },
  { .Position = vec3(1.0f, -1.0f,  1.0f), .Normal = vec3( 0.0f,  0.0f,  1.0f) },
  { .Position = vec3(1.0f,  1.0f,  1.0f), .Normal = vec3( 0.0f,  0.0f,  1.0f) },
  { .Position = vec3(1.0f,  1.0f,  1.0f), .Normal = vec3( 0.0f,  0.0f,  1.0f) },
  { .Position = vec3(-1.0f,  1.0f,  1.0f), .Normal = vec3( 0.0f,  0.0f,  1.0f) },
  { .Position = vec3(-1.0f, -1.0f,  1.0f), .Normal = vec3( 0.0f,  0.0f,  1.0f) },

  { .Position = vec3(-1.0f,  1.0f,  1.0f), .Normal = vec3(-1.0f,  0.0f,  0.0f) },
  { .Position = vec3(-1.0f,  1.0f, -1.0f), .Normal = vec3(-1.0f,  0.0f,  0.0f) },
  { .Position = vec3(-1.0f, -1.0f, -1.0f), .Normal = vec3(-1.0f,  0.0f,  0.0f) },
  { .Position = vec3(-1.0f, -1.0f, -1.0f), .Normal = vec3(-1.0f,  0.0f,  0.0f) },
  { .Position = vec3(-1.0f, -1.0f,  1.0f), .Normal = vec3(-1.0f,  0.0f,  0.0f) },
  { .Position = vec3(-1.0f,  1.0f,  1.0f), .Normal = vec3(-1.0f,  0.0f,  0.0f) },

  { .Position = vec3(1.0f,  1.0f,  1.0f), .Normal = vec3( 1.0f,  0.0f,  0.0f) },
  { .Position = vec3(1.0f,  1.0f, -1.0f), .Normal = vec3( 1.0f,  0.0f,  0.0f) },
  { .Position = vec3(1.0f, -1.0f, -1.0f), .Normal = vec3( 1.0f,  0.0f,  0.0f) },
  { .Position = vec3(1.0f, -1.0f, -1.0f), .Normal = vec3( 1.0f,  0.0f,  0.0f) },
  { .Position = vec3(1.0f, -1.0f,  1.0f), .Normal = vec3( 1.0f,  0.0f,  0.0f) },
  { .Position = vec3(1.0f,  1.0f,  1.0f), .Normal = vec3( 1.0f,  0.0f,  0.0f) },

  { .Position = vec3(-1.0f, -1.0f, -1.0f), .Normal = vec3( 0.0f, -1.0f,  0.0f) },
  { .Position = vec3(1.0f, -1.0f, -1.0f), .Normal = vec3( 0.0f, -1.0f,  0.0f) },
  { .Position = vec3(1.0f, -1.0f,  1.0f), .Normal = vec3( 0.0f, -1.0f,  0.0f) },
  { .Position = vec3(1.0f, -1.0f,  1.0f), .Normal = vec3( 0.0f, -1.0f,  0.0f) },
  { .Position = vec3(-1.0f, -1.0f,  1.0f), .Normal = vec3( 0.0f, -1.0f,  0.0f) },
  { .Position = vec3(-1.0f, -1.0f, -1.0f), .Normal = vec3( 0.0f, -1.0f,  0.0f) },

  { .Position = vec3(-1.0f,  1.0f, -1.0f), .Normal = vec3( 0.0f,  1.0f,  0.0f) },
  { .Position = vec3(1.0f,  1.0f, -1.0f), .Normal = vec3( 0.0f,  1.0f,  0.0f) },
  { .Position = vec3(1.0f,  1.0f,  1.0f), .Normal = vec3( 0.0f,  1.0f,  0.0f) },
  { .Position = vec3(1.0f,  1.0f,  1.0f), .Normal = vec3( 0.0f,  1.0f,  0.0f) },
  { .Position = vec3(-1.0f,  1.0f,  1.0f), .Normal = vec3( 0.0f,  1.0f,  0.0f) },
  { .Position = vec3(-1.0f,  1.0f, -1.0f), .Normal = vec3( 0.0f,  1.0f,  0.0f) },
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
  glEnable(GL_DEPTH_TEST);

  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetKeyCallback(window, keyCallback);

	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
}

Renderer makeRenderer() {
  Program peaceProgram = Program("./renderer/shaders/main.peace.vert", "./renderer/shaders/main.peace.frag");
  Program boardProgram = Program("./renderer/shaders/main.vert", "./renderer/shaders/main.frag");
  Renderer output = {
    .boardProgram = boardProgram,
    .peaceProgram = peaceProgram,
    .boardMesh = Mesh(boardVertices),
    .cubeMesh = Mesh(cubeVertices),
    .camera = Camera(),
    .projection = make_projection_angle(45.0, 1, 0.1, 100),
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

#include <glm/gtx/string_cast.hpp>

mat4 model(Peace peace, ivec2 boardSize, vec3 rotationVector, float rotationAngle) {
  float scale = 0.1;
  float eps = 0.001;

  vec2 bs = vec2(boardSize);
  vec2 pp = vec2(peace.position + 1) - (bs / 2.0f);
  vec3 position = vec3(pp / (bs / 2.0f) - (vec2(1.0) / bs), scale + eps);
  mat4 trans = translate(position);

  mat4 r = rotate(mat4(1.0), rotationAngle, rotationVector);
  return r * trans * mat4(mat3(scale));
}

void render(Renderer &renderer, Game &game) {
  renderer.time = glfwGetTime();
  // renderer.camera.position.x = 2.0 * cosf(renderer.time);
  // renderer.camera.position.z = 2.0 * sinf(renderer.time);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  renderer.boardProgram.use();
  renderer.boardProgram.setMat4("model", make_model(translations[0], rotationVectors[0], M_PI / 2.0f));
  renderer.boardProgram.setMat4("view", renderer.camera.viewMatrix());
  renderer.boardProgram.setMat4("projection", renderer.projection);
  renderer.boardMesh.Draw(renderer.boardProgram);

  renderer.peaceProgram.use();
  renderer.peaceProgram.setMat4("view", renderer.camera.viewMatrix());
  renderer.peaceProgram.setMat4("projection", renderer.projection);
  for (int i = 0; i < game.board.whitePeaces.size(); i++) {
    renderer.peaceProgram.setMat4("model", model(game.board.whitePeaces[i], game.board.size, -rotationVectors[0], M_PI / 2.0f));
    renderer.cubeMesh.Draw(renderer.peaceProgram);
  }
  for (int i = 0; i < game.board.blackPeaces.size(); i++) {
    renderer.peaceProgram.setMat4("model", model(game.board.blackPeaces[i], game.board.size, -rotationVectors[0], M_PI / 2.0f));
    renderer.cubeMesh.Draw(renderer.peaceProgram);
  }

  glfwSwapBuffers(window);
  glfwPollEvents();
}

bool should_close() {
  return glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && 
    glfwWindowShouldClose(window) == 0;
}

#endif
