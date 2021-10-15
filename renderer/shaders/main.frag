#version 330 core

in vec2 fragPos;
out vec4 FragColor;

void main() {
  ivec2 sector = ivec2((fragPos + 1) / 0.25) % 2;
  bvec2 bsector = bvec2(sector);
  if (bsector.y) {
    FragColor = vec4(bsector.x, 0.0, 0.0, 1.0);
  }
  else {
    FragColor = vec4(!bsector.x, 0.0, 0.0, 1.0);
  }
}
