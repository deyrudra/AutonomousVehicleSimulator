# Shaders

Situation: Want to have a cube with different colours on each side.

Solutions:
- Option 1: Per-vertex Colours
	- This allows you to colour distinct faces

- Option 2: Lighting-Based Shading
	- This allows you to add lighting for realistic shading


Here's a quick overview of the graphics pipeline in order:
1. Vertex Data (your cube's positions/colors/normals)
	- Runs once per vertex
	- Your main jobs here:
		- Transform vertex positions (model → view → projection space)
		- Pass data (like colors/normals) to fragment shader
2. Vertex Shader (processes each vertex)
	- Runs once per pixel that your object covers
	- Your main jobs here:
		- Determine final color for each pixel
		- Can use interpolated values from vertex shader
3. Primitive Assembly (forms triangles)
4. Rasterization (converts to pixels)
5. Fragment Shader (colors each pixel)
6. Framebuffer (final image)



So in an example of how to colour your object you could:
```cpp
// Example vertex shader
#version 330 core
layout(location = 0) in vec3 aPos;  // Vertex position from CPU
layout(location = 1) in vec3 aColor; // Vertex color from CPU

out vec3 vertexColor;  // Pass to fragment shader

uniform mat4 model, view, projection; // Transformation matrices

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vertexColor = aColor;  // Pass-through color
}
```
- This Vertex Shader code is run in step 1 of the pipeline, and thus runs once per vertex.
- Over here, vertex positions are passed `aPos` and vertex colours are passed `aColor`.
- In this case we are outputing `aColor` as the `vertexColor` such that in step 2, we can use this.
	- If we didn't care about anything else, then we would output the colour `aColor` as `FragColor`.

```cpp
// Example fragment shader
#version 330 core
in vec3 vertexColor;  // From vertex shader (automatically interpolated!)
out vec4 FragColor;   // Final pixel color

void main() {
    FragColor = vec4(vertexColor, 1.0); 
}
```
- This Fragment Shader code is run in step 2 of the pipeline, and thus runs once per pixel.
- Over here the previous `vertexColor` is passed and we are outputin `FragColor`. 
- **Note**: vec4 is a vector with 4 slots. vec3 is a vector with 3 slots.