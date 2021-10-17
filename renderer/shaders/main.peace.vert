#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

struct Light {
  vec3 color;
  vec3 position;
};

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform Light light;
uniform vec3 viewPos;

out vec3 fragPosition;
out vec3 lightColor;

void main() {
  mat3 modelWithoutTranslation = mat3(transpose(inverse(model)));

  gl_Position = projection * view * model * vec4(aPos, 1);
  vec3 outNormal = modelWithoutTranslation * aNormal;
  fragPosition = vec3(model * vec4(aPos, 1));

  float ambientStrength = 0.1;
  vec3 ambient = ambientStrength * light.color;

  vec3 norm = normalize(outNormal);
  vec3 lightDir = normalize(light.position - fragPosition);

  float lightAmount = dot(norm, lightDir);
  float diff = max(lightAmount, 0.0);
  vec3 diffuse = diff * light.color;

  float specularStrength = 1.0;
  vec3 reflection = reflect(-lightDir, norm);
  vec3 viewDir = normalize(viewPos - fragPosition);
  float spec = pow(max(dot(reflection, viewDir), 0.0), 64 );
  vec3 specular = specularStrength * spec * lightColor;

  lightColor = (diffuse + ambient + specular);
}
