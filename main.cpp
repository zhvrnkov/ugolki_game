#include <glm/glm.hpp>
#include <cmath>
#include "renderer/renderer.h"
#include "renderer/camera/camera.h"

using namespace glm;
using namespace std;

static Renderer *rendererRef;

static void scrollCallback(double xoffset, double yoffset) {
  cout << "scrollCallback" << endl;
}

#include <glm/gtx/string_cast.hpp>

vec2 toScreen(vec4 src) {
  vec3 homo = vec3(src.x, src.y, src.z) / src.w;
  return vec2(homo.x + 1.0, homo.y - 1.0) * (vec2(SCR_WIDTH, -SCR_HEIGHT) / 2.0f);
}

static void mouseButtonCallback(double x, double y) {
  float angle = M_PI / 2.0f;
  mat4 model = make_model(translations[0], rotationVectors[0], angle);
  mat4 view = rendererRef->camera.viewMatrix();
  mat4 projection = rendererRef->projection;
//  mat4 inv = inverse(projection * view * model);
  float fx = x;
  float fy = y;
  mat4 t = projection * view * model;
  vec4 tr = t * vec4(1.0f, 1.0f, 0.0f, 1.0f);
  vec4 tl = t * vec4(1.0f, -1.0f, 0.0f, 1.0f);
  vec4 br = t * vec4(-1.0f, 1.0f, 0.0f, 1.0f);
  vec4 bl = t * vec4(-1.0f, -1.0f, 0.0f, 1.0f);
  vec3 clickPos = inverse(mat3(t)) * vec3(x, y, 0.0f);

  ivec2 sector = ivec2(floor((clickPos + 1.0f) * 4.0f));
  
  cout << "click: " << to_string(clickPos) << endl;
  cout << "tr: " << to_string(toScreen(tr)) << endl;
  cout << "tl: " << to_string(toScreen(tl)) << endl;
  cout << "br: " << to_string(toScreen(br)) << endl;
  cout << "bl: " << to_string(toScreen(bl)) << endl << endl;
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
  rendererRef = &renderer;
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
