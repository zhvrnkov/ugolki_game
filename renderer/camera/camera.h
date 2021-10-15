#ifndef camera_header
#define camera_header

#include <glm/glm.hpp>
using namespace glm;

typedef struct {
  vec3 up;
  vec3 direction;
  const vec3 initialDirection;
  vec3 position;
} Camera;

Camera makeDefaultCamera();
mat4 make_view(Camera *camera);
mat4 make_projection(float w, float h, float n, float f);
mat4 make_projection_angle(float fovY, float aspectRatio, float n, float f);
mat4 make_model(vec3 translation, vec3 rotationVector, float rotationAngle);

#endif
