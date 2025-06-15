#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "shader.h"
#include "rectangle.h"
#include "cube.h"
#include "camera.h"
#include "terrain.h"
#include "model.h"
#include "mesh.h"

#define xRes 1280
#define yRes 720

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(xRes, yRes, "My special lil window", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST); // required for 3D

    Shader shader("vertex.glsl", "fragment.glsl");

    unsigned int cubeVAO = createCubeVAO();

    Camera camera(xRes, yRes, glm::vec3(0.0f, 0.0f, 2.0f));

    // Sine Wave Terrain Stuff
    std::vector<float> terrainVertices;
    std::vector<unsigned int> terrainIndices;
    unsigned int terrainVAO = createTerrainVAO(100, 100, 0.2f, terrainVertices, terrainIndices);

    // Flat Terrain Stuff
    std::vector<float> flatVertices;
    std::vector<unsigned int> flatIndices;
    unsigned int flatTerrainVAO = createFlatTerrainVAO(50, 50, 0.2f, flatVertices, flatIndices);

    // Loading Spiderman Model
    Model model("Head.stl");


    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        // Set lighting uniforms
        shader.setVec3("objectColor", 1.0f, 0.5f, 0.31f); // Orange color
        shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);   // White light
        shader.setVec3("lightPos", 5.0f, 5.0f, 5.0f);     // Light position
        shader.setVec3("viewPos", 0.0f, 0.0f, 3.0f);      // Camera position

        camera.Inputs(window);

        camera.Matrix(45.0f, 0.1f, 100.0f, shader, "camMatrix");


        //Sine Wave Terrain
        glBindVertexArray(terrainVAO);
        glDrawElements(GL_TRIANGLES, terrainIndices.size(), GL_UNSIGNED_INT, 0);
        
        // Flat Terrain
        shader.setVec3("objectColor", 0.5f, 0.5f, 0.5f); // Making Terrain Grey
        glm::mat4 flat_terrain_model = glm::mat4(1.0f);
        flat_terrain_model = glm::translate(flat_terrain_model, glm::vec3(-5.0f, -1.0f, -5.0f));
        shader.setMat4("model", glm::value_ptr(flat_terrain_model));

        glBindVertexArray(flatTerrainVAO);
        glDrawElements(GL_TRIANGLES, flatIndices.size(), GL_UNSIGNED_INT, 0);

        // Cube
        glm::mat4 cube_model = glm::mat4(1.0f);
        cube_model = glm::translate(cube_model, glm::vec3(-1.0f, 1.0f, 0.0f)); // move left and up
        shader.setMat4("model", glm::value_ptr(cube_model));
        glBindVertexArray(cubeVAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // Spiderman Model
        glm::mat4 spiderman_model = glm::mat4(1.0f);
        spiderman_model = glm::translate(spiderman_model, glm::vec3(0, -1.0f, -5.0f));
        spiderman_model = glm::scale(spiderman_model, glm::vec3(0.5f));
        shader.setMat4("model", glm::value_ptr(spiderman_model));
        model.Draw();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}