#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO;

    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    void Draw() const;

private:
    unsigned int VBO, EBO;
    void setupMesh();
};

#endif