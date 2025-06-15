// terrain.cpp
#include <vector>
#include <cmath>
#include <glad/glad.h>

unsigned int createTerrainVAO(int width, int depth, float scale, std::vector<float>& outVertices, std::vector<unsigned int>& outIndices) {
    for (int z = 0; z <= depth; ++z) {
        for (int x = 0; x <= width; ++x) {
            float xpos = (float)x * scale;
            float zpos = (float)z * scale;

            float height = sinf(x * 0.3f) * cosf(z * 0.3f); // simple wave pattern

            outVertices.insert(outVertices.end(), {
                xpos, height, zpos,   // position
                0.0f, 1.0f, 0.0f      // normal (up, temp)
                });
        }
    }

    for (int z = 0; z < depth; ++z) {
        for (int x = 0; x < width; ++x) {
            unsigned int i = z * (width + 1) + x;
            outIndices.insert(outIndices.end(), {
                i, i + 1, i + width + 1,
                i + 1, i + width + 2, i + width + 1
                });
        }
    }

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, outVertices.size() * sizeof(float), outVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, outIndices.size() * sizeof(unsigned int), outIndices.data(), GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    return VAO;
}


unsigned int createFlatTerrainVAO(int width, int depth, float scale, std::vector<float>& outVertices, std::vector<unsigned int>& outIndices) {
    for (int z = 0; z <= depth; ++z) {
        for (int x = 0; x <= width; ++x) {
            float xpos = (float)x * scale;
            float zpos = (float)z * scale;

            float height = 0.0f; // flat height

            outVertices.insert(outVertices.end(), {
                xpos, height, zpos,
                0.0f, 1.0f, 0.0f // normals pointing up
                });
        }
    }

    for (int z = 0; z < depth; ++z) {
        for (int x = 0; x < width; ++x) {
            unsigned int i = z * (width + 1) + x;
            outIndices.insert(outIndices.end(), {
                i, i + 1, i + width + 1,
                i + 1, i + width + 2, i + width + 1
                });
        }
    }

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, outVertices.size() * sizeof(float), outVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, outIndices.size() * sizeof(unsigned int), outIndices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    return VAO;
}
