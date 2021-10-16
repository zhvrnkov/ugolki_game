#ifndef renderer_h
#define renderer_h

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "shader.h"
#include "mesh.h"
#include <vector>

#define SCR_WIDTH 800.0
#define SCR_HEIGHT 800.0
#define UNIT_SIZE 0.025f

using namespace glm;
using namespace std;

typedef struct {
} RenderingContext;

typedef struct {
  Program mainProgram;
  RenderingContext context;
} Renderer;

typedef struct {
  void (*mouseButtonCallback)(double, double);
  void (*scrollCallback)(double, double);
  void (*keyCallback)(int, int, int, int);
} WindowPresenter;

static vector<Vertex> vertices {
  { .Position = vec3(-1.0f, -1.0f, 0.0f), .Normal = vec3(0.0f, 0.0f, 1.0f) },
  { .Position = vec3(1.0f, -1.0f, 0.0f),  .Normal = vec3(0.0f, 0.0f, 1.0f) },
  { .Position = vec3(1.0f,  1.0f, 0.0f),  .Normal = vec3(0.0f, 0.0f, 1.0f) },
  { .Position = vec3(1.0f,  1.0f, 0.0f),  .Normal = vec3(0.0f, 0.0f, 1.0f) },
  { .Position = vec3(-1.0f,  1.0f, 0.0f), .Normal = vec3(0.0f, 0.0f, 1.0f) },
  { .Position = vec3(-1.0f, -1.0f, 0.0f), .Normal = vec3(0.0f, 0.0f, 1.0f) },
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
  RenderingContext context;
  Renderer output = {
    .mainProgram = mainProgram,
    .context = context
  };
  return output;
}

void render(Renderer *renderer) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  Mesh mesh = Mesh(vertices);
  mesh.Draw(renderer->mainProgram);

  // renderMainProgram(renderer);
  glfwSwapBuffers(window);
  glfwPollEvents();
}

bool should_close() {
  return glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && 
    glfwWindowShouldClose(window) == 0;
}

#endif
