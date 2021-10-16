#ifndef game_h
#define game_h

#include <glm/glm.hpp>

#define PEACES_COUNT 4 * 4

using namespace glm;

typedef struct {
  ivec2 position;
} Peace;

typedef struct {
  ivec2 size;
  Peace whitePeaces[PEACES_COUNT];
  Peace blackPeaces[PEACES_COUNT];
} Board;

typedef struct {
  Board board;
  bool isWhiteTurn;
} Game;

#endif
