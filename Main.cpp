#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#define xRes 1024
#define yRes 1024


int main() {
	// Initializing GLFW / Graphics Library Framework
	glfwInit();
	
	// Specifying OpenGL version and profile.
	// The core profile hosts the modern functionality of OPENGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// Creating GLFW Window. glfwMakeContextCurrent makes the current OpenGL context,
	// the window, the current one on the calling thread.
	GLFWwindow* window = glfwCreateWindow(xRes, yRes, "AVS", NULL, NULL);
	if (window == NULL) {
		std::cerr << "The widnow could not be created." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// GLAD is used to load the address of the OpenGL function pointers which is OS-specific. 
	gladLoadGL();

	// Creating the viewport/rendering area of our window
	glViewport(0, 0, xRes, yRes);

	// Creating a sky blue background, glfwSwapBuffers swaps the front and back buffers.
	glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window)) {
		// This function actively polls the events happening to the window; this includes window movement, mouse movements, and sort of
		// input, etc. Without this, the window will be in state of "not responding".
		glfwPollEvents();
	}

	// This function destoys the window.
	glfwDestroyWindow(window);

	// This function terminates the glfw API
	glfwTerminate();

	// Terminating GLFW
	glfwTerminate();
}	