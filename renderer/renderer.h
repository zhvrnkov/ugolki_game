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
#include "light.h"

#define SCR_WIDTH 960.0
#define SCR_HEIGHT 960.0
#define UNIT_SIZE 0.025f

using namespace glm;
using namespace std;

struct Renderer {
public:
  Program boardProgram;
  Program peaceProgram;
  Program lightProgram;
  Mesh boardMesh;
  Mesh cubeMesh;
  Camera camera;
  mat4 projection;
  float time;
  Light light;
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

static Light makeLight() {
  Light light = {
    .position = vec3(1.0f, 1.0f, -5.0f),
    .ambient = vec3(0.0f),
    .diffuse = vec3(0.0f),
    .specular = vec3(1.0f),
    .color = vec3(1.0f)
  };
  return light;
}

Renderer makeRenderer() {
  Program peaceProgram = Program("./renderer/shaders/main.peace.vert", "./renderer/shaders/main.peace.frag");
  Program boardProgram = Program("./renderer/shaders/main.vert", "./renderer/shaders/main.frag");
  Program lightProgram = Program("./renderer/shaders/main.lightning.vert", "./renderer/shaders/main.lightning.frag");
  Renderer output = {
    .boardProgram = boardProgram,
    .peaceProgram = peaceProgram,
    .lightProgram = lightProgram,
    .boardMesh = Mesh(boardVertices),
    .cubeMesh = Mesh(cubeVertices),
    .camera = Camera(),
    .projection = make_projection_angle(45.0, 1, 0.1, 100),
    .time = 0.0,
    .light = makeLight()
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

static mat4 model(Peace peace, ivec2 boardSize, vec3 rotationVector, float rotationAngle) {
  float scale = 0.1;
  float eps = 0.001;

  vec2 bs = vec2(boardSize);
  vec2 pp = vec2(peace.position + 1) - (bs / 2.0f);
  vec3 position = vec3(pp / (bs / 2.0f) - (vec2(1.0) / bs), scale + eps);
  mat4 trans = translate(position);

  mat4 r = rotate(mat4(1.0), rotationAngle, rotationVector);
  return r * trans * mat4(mat3(scale));
}

static void updateLight(Program program, Light light) {
  program.setVec3("light.color", light.color);
  program.setVec3("light.position", light.position);
}

void render(Renderer &renderer, Game &game) {
  float angle = M_PI / 2.0f;
  renderer.time = glfwGetTime();
  // renderer.camera.position.x = 2.0 * cosf(renderer.time);
  // renderer.camera.position.z = 2.0 * sinf(renderer.time);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  renderer.boardProgram.use();
  renderer.boardProgram.setMat4("model", make_model(translations[0], rotationVectors[0], angle));
  renderer.boardProgram.setMat4("view", renderer.camera.viewMatrix());
  renderer.boardProgram.setMat4("projection", renderer.projection);
  renderer.boardMesh.Draw(renderer.boardProgram);

  renderer.peaceProgram.use();
  renderer.peaceProgram.setMat4("view", renderer.camera.viewMatrix());
  renderer.peaceProgram.setMat4("projection", renderer.projection);
  renderer.peaceProgram.setVec3("viewPos", renderer.camera.position);
  updateLight(renderer.peaceProgram, renderer.light);
  renderer.peaceProgram.setVec3("objectColor", vec3(0.8f));
  for (int i = 0; i < game.board.whitePeaces.size(); i++) {
    renderer.peaceProgram.setMat4("model", model(game.board.whitePeaces[i], game.board.size, -rotationVectors[0], angle));
    renderer.cubeMesh.Draw(renderer.peaceProgram);
  }
  renderer.peaceProgram.setVec3("objectColor", vec3(0.2f));
  for (int i = 0; i < game.board.blackPeaces.size(); i++) {
    renderer.peaceProgram.setMat4("model", model(game.board.blackPeaces[i], game.board.size, -rotationVectors[0], angle));
    renderer.cubeMesh.Draw(renderer.peaceProgram);
  }

  renderer.lightProgram.use();
  renderer.light.position.x = cosf(renderer.time);
  renderer.light.position.y = (sinf(renderer.time) + 1.0f) / 2.0f;
  renderer.light.position.z = sinf(renderer.time / 4) - 3.0;
  renderer.lightProgram.setMat4("model", make_model(renderer.light.position, vec3(1.0f), 0.0f) * mat4(mat3(0.125f)));
  renderer.lightProgram.setMat4("view", renderer.camera.viewMatrix());
  renderer.lightProgram.setMat4("projection", renderer.projection);
  updateLight(renderer.lightProgram, renderer.light);
  renderer.cubeMesh.Draw(renderer.lightProgram);

  glfwSwapBuffers(window);
  glfwPollEvents();
}

bool should_close() {
  return glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && 
    glfwWindowShouldClose(window) == 0;
}

#endif
