#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
using namespace glm;

typedef struct {
  vec3 position;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;

  vec3 color;
} Light;

#endif
