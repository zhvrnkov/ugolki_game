#ifndef game_h
#define game_h

#include <glm/glm.hpp>
#include <vector>

using namespace glm;

struct Peace {
  ivec2 position;
};

struct Board {
  ivec2 size;
  vector<Peace> whitePeaces;
  vector<Peace> blackPeaces;
};

struct Game {
  Board board;
  bool isWhiteTurn;
};

#endif
