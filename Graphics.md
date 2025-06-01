# Graphics

Object's Geometry
- Built from geometric primitives such as: points, lines, and triangles
- For a 3D object you list the coordinates of it's vertices; to do this
we would use the datatype GLfloat.
- For anything more complex than the simple shapes, you typically define
indices. Indices save memory since the premise is based on reusing vertices.

Storing Geometry Data in Buffers (VBOs, VAOs, and EBOs)
- Overview: 
	VBO (Vertex Buffer Object):
	Holds the actual vertex data, such as coordinates, colors, and texture coordinates. 
	EBO (Element Buffer Object):
	Stores a list of numbers (indices) that specify which vertices from the VBO should be used to draw a particular shape or primitive. 
	VAO (Vertex Array Object):
	Manages the state of vertex attributes, including which VBOs and EBOs are currently bound, and how vertex attributes are interpreted. 

- What are VAOs? (Vertex Array Objects)
	- To generate one of Vertex Arrays we use: `glGenVertexArrays(# of vertices, &object address)`
	- To select the vertex array as your current vertex array, use the `glBindVertexArray(&object address)` function.
	- Basically a VAO is what you use to access your Vertex Buffer Object (VBO). It basically bundles together all these
	buffers and allows you to utilize them easier.
- What are VBOs? (Vertex Buffer Objects)
	- To generate one of these buffers we use: `glGenBuffer(# of vertices, &object address)`
	- To select the buffer as your current buffer, use the `glBindBuffer` function.
	- VBOs are basically arrays which store the data that you want to hold at your vertex. Such as position, or colour.
		- To populate the data we use `glBufferData` function.
- Remember that the VAO has to be declared before the VBO.
- What are EBOs? (Element Buffer Object)
	- A buffer that stores a list of numbers (indices) that specify which vertices from the VBO should be used to draw
	a particular shape or primitive.

- How to tell OpenGL how to interpret the vertex data in your buffer, and connect it to a vertex attribute.
	```
	glVertexAttribPointer(
		GLuint index,        // Attribute location in shader (e.g., layout(location = 0))
		GLint size,          // Number of components (e.g., 3 for vec3)
		GLenum type,         // Data type (e.g., GL_FLOAT)
		GLboolean normalized,// Normalize? (usually GL_FALSE)
		GLsizei stride,      // Byte offset between consecutive vertices
		const void *pointer  // Offset where the attribute data starts
	);
	```
	- Using this function, we can specify that the buffer represents this vertex attribute (ex. position or colour)
	and here is how it is laid out in the array.

	- Afterwards, we run `glBindVertexArray(0)` to enable the attribute.



	


