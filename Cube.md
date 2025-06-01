# Cube

Creating a cube in OpenGL, and also animating it.

Creating the cube:
```cpp
#include "cube.h"
#include <glad/glad.h>

float cubeVertices[] = {
    -0.5f, -0.5f, -0.5f,  // back face
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,  // front face
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f
};

unsigned int cubeIndices[] = {
    0,1,2, 2,3,0, // each of these are like one side of the cube.
    4,5,6, 6,7,4,
    0,4,7, 7,3,0,
    1,5,6, 6,2,1,
    4,5,1, 1,0,4,
    3,2,6, 6,7,3
};

unsigned int createCubeVAO() {
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    return VAO;
}
```

Animating the Cube: (in the main file, near the while loop and some stuff above it)
```
    glEnable(GL_DEPTH_TEST); // required for 3D

    Shader shader("vertex.glsl", "fragment.glsl");

    unsigned int cubeVAO = createCubeVAO();

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        glm::mat4 identityMatrix = glm::mat4(1.0f);
        glm::mat4 model = glm::rotate(identityMatrix, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3));
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)xRes / yRes, 0.1f, 100.0f);
        glm::mat4 mvp = proj * view * model;

        shader.setMat4("mvp", glm::value_ptr(mvp));

        glBindVertexArray(cubeVAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
```
- mat4: 4x4 matrix which transforms
- identityMatrix: An identity matrix which we apply all the transformations to.
- cubeVAO is a our cube object; we select the object by setting `glBindVertexArray(cubeVAO)`
- the `glm::rotate` function takes in the identity matrix (arg 1), rotates it an angle in radians (arg 2),
chooses the axis to rotate about in 3D space (the vector is typically normalized, otherwise it will be
normalized automatically (arg 3)
- the `glm::translate` function translates the identity matrix gives (arg 1), in a direction using a vector (arg 2)
- the `glm::perspective` creates a perspective projection matrix which mimics how a human eye or camera sees the 3D world.
In other words, objects farther away appear smaller. The arguments are:
    - fovRadians (arg1): Field of view in the y-direction in radians (left and right)
    - aspectRatio (arg2): width / height of your window  
    - nearPlane (arg3): Distance to the near clipping plane (must be > 0), i.e. shortest render distance
    - farPlane (arg4): Distance to the far clipping plane, i.e. farthest render distance
- To combine all these we just multiply the matrices to create a mvp (model view projection) matrix.