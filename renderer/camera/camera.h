#ifndef camera_header
#define camera_header

#include <glm/glm.hpp>
using namespace glm;

mat4 translate(vec3 translation);
mat4 make_projection(float w, float h, float n, float f);
mat4 make_projection_angle(float fovY, float aspectRatio, float n, float f);
mat4 make_model(vec3 translation, vec3 rotationVector, float rotationAngle);

struct Camera {
  public:
  vec3 up;
  vec3 direction;
  vec3 position;

  Camera(vec3 up_in, vec3 direction_in, vec3 position_in)
    : up(up_in)
    , direction(direction_in)
    , position(position_in)
    , initialDirection(this->direction) 
  {};

  Camera()
    : up(vec3(0.0, 1.0, 0.0))
    , direction(vec3(0.0, 0.0, -1.0))
    , position(vec3(0.0, 1.5, 1.5))
    , initialDirection(this->direction) 
  {};

  mat4 viewMatrix() {
    vec3 dfp = position;// normalize(position - direction);
    vec3 newZ = dfp;
    vec3 newX = normalize(cross(up, newZ));
    vec3 newY = normalize(cross(newZ, newX));
    mat4 tr = mat4(1.0);
    tr[0] = vec4(newX.x, newY.x, newZ.x, tr[0].w);
    tr[1] = vec4(newX.y, newY.y, newZ.y, tr[1].w);
    tr[2] = vec4(newX.z, newY.z, newZ.z, tr[2].w);
    return tr * translate(-(position));
  }

  private:
  const vec3 initialDirection;
};

#endif
