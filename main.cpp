#include <glm/glm.hpp>
#include <cmath>
#include "renderer/renderer.h"

using namespace glm;
using namespace std;


static void scrollCallback(double xoffset, double yoffset) {
  cout << "scrollCallback" << endl;
}

static void mouseButtonCallback(double x, double y) {
  cout << "Click in (x: " << x << ", y:" << y << ")" << endl;
}

static void keyCallback(int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS) {
    cout << "Key: " << key << endl;
  }
}

int main() {
  setupWindow();
  Renderer renderer = makeRenderer();
  windowPresenter.mouseButtonCallback = mouseButtonCallback;
  windowPresenter.scrollCallback = scrollCallback;
  windowPresenter.keyCallback = keyCallback;

  for (size_t i = 0; should_close(); i++) {
    render(&renderer);
  }

  glfwTerminate();
  return 0;
}
