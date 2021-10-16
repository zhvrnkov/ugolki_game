#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

#include <string>
#include <vector>
using namespace std;

#define MAX_BONE_INFLUENCE 4

struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
};

class Mesh {
 public:
  // mesh Data
  vector<Vertex> vertices;
  unsigned int VAO;

  // constructor
  Mesh(vector<Vertex> vertices)
    {
      this->vertices = vertices;
      setupMesh();
    }

  // render the mesh
  void Draw(Program &shader) 
  {
    glUseProgram(shader.ID);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
  }

 private:
  unsigned int VBO;

  void setupMesh()
  {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    glBindVertexArray(0);
  }
};
#endif
