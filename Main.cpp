#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#define xRes 1024
#define yRes 1024

// Rectangle Vertices + Indices
float vertices[] = {
	// positions        // optional: colors or texcoords
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
};

unsigned int indices[] = {
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};


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



	// Shader Compilation ---------------------------------------------------------

	// Vertex Shader source code
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	//Fragment Shader source code
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(0.8f, 0.1f, 0.06f, 1.0f);\n"
		"}\n\0";

	// 1. Create and compile the vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// (You should check for compilation errors here)

	// 2. Create and compile the fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// (You should check for compilation errors here)

	// 3. Link the shaders into a shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// (You should check for linking errors here)

	// 4. Clean up shaders (they're already linked into the program)
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// ----------------------------------------------------------------------------


	// Creating a rectangle -------------------------------------------------------
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind Vertex Array Object
	glBindVertexArray(VAO);

	// Bind Vertex Buffer Object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Copy vertex data into buffer (VBO)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind Element Buffer Object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// Copy index data into buffer (EBO)
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Set vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind (optional for safety)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// -----------------------------------------------------------------------------




	while (!glfwWindowShouldClose(window))
	{
		// Drawing in the skyblue background ---------------------------------------
		glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// -------------------------------------------------------------------------
		
		// Drawing in rectangle ----------------------------------------------------
		
		// Use your shader program
		glUseProgram(shaderProgram);
		// Bind the VAO
		glBindVertexArray(VAO);
		// Draw the rectangle using indices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// -------------------------------------------------------------------------

		// Swapping buffers to update the image.
		glfwSwapBuffers(window);

		// This function actively polls the events happening to the window. (NEED THIS)
		glfwPollEvents();
	}

	

	// This function destoys the window.
	glfwDestroyWindow(window);

	// This function terminates the glfw API
	glfwTerminate();

	// Terminating GLFW
	glfwTerminate();
}	