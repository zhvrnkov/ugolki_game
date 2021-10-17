#include <glm/glm.hpp>
#include <cmath>
#include "renderer/renderer.h"
#include "renderer/camera/camera.h"

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

Game makeGame();

int main() {
  setupWindow();

  Game game = makeGame();
  Renderer renderer = makeRenderer();
  windowPresenter.mouseButtonCallback = mouseButtonCallback;
  windowPresenter.scrollCallback = scrollCallback;
  windowPresenter.keyCallback = keyCallback;

  for (size_t i = 0; should_close(); i++) {
    render(renderer, game);
  }

  glfwTerminate();
  return 0;
}

Game makeGame() {
  ivec2 boardSize = ivec2(8, 8);
  ivec2 peacesDimension = ivec2(3, 3);
  ivec2 shift = boardSize - peacesDimension;
  vector<Peace> blackPeaces;
  for (int x = 0; x < peacesDimension.x; x++) {
    for (int y = 0; y < peacesDimension.y; y++) {
      blackPeaces.push_back(Peace { .position = ivec2(x, y) });
    }
  }

  vector<Peace> whitePeaces;
  for (int x = 0; x < peacesDimension.x; x++) {
    for (int y = 0; y < peacesDimension.y; y++) {
      whitePeaces.push_back(Peace { .position = shift + ivec2(x, y) });
    }
  }
  Board board = {
    .size = boardSize,
    .whitePeaces = whitePeaces,
    .blackPeaces = blackPeaces
  };
  Game game = {
    .board = board,
    .isWhiteTurn = true
  };
  return game;
}
