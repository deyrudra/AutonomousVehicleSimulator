// File: main.cpp
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "rectangle.h"
#include "cube.h"
#include "camera.h"

#define xRes 1024
#define yRes 1024

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



        //glm::mat4 model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        //glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3));
        //glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)xRes / yRes, 0.1f, 100.0f);
        //glm::mat4 mvp = proj * view * model;

        //shader.setMat4("mvp", glm::value_ptr(mvp));
        //shader.setMat4("model", glm::value_ptr(model));

        glBindVertexArray(cubeVAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}