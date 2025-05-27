# Setup

Basically, to setup we need to have the necessary libraries: GLFW, GLAD. Additionally, we have to start an empty C++ project in Visual Studio.

1. Create an empty c++ project in Visual Studio.
2. In the project directory create a folder called `Libraries`, with two subfolders called `include` and `lib`.
3. Download and extract the GLAD library, from this link: https://glad.dav1d.de/.
	- Configure it as followed: Language = C/C++, Specification = OpenGL, API->gl=3.3, Profile = Core, don't touch anything else, then click generate.
	- After that, click on the zip folder that comes to download it.
4. Download and extract GLFW from this link: https://www.glfw.org/, click the big Download GLFW 3.4 button. Then in the extracted folder, create
a folder called build.
5. Download and install CMake from this link: https://cmake.org/download/, download windows x64 installer.
6. Open CMake and for the source code select the GLFW folder that you extracted. Then for the build binaries directory, select the build folder that
you created at the end of step 4. Then click on configure and then generate.
7. Now we are going to build GLFW. Open that build folder that you previously created, and open up `GLFW.sln` in Visual Studio. Right click the Solution
and press "Build Solution". If errors happen, then restart from step 4. Then open up the build folder again, then src, then Debug, then copy the glfw3.lib
file and paste it in your project's `Libraries/lib/` folder.
8. Then go into the glfw folder that you extracted previously, then go into the include folder and copy the GLFW folder into your project's
`Libraries/include/` folder.
9. Open up the extracted glad folder, and then go into include. Copy the two files that are there and put it in the `Libraries/include/` folder. Then
go a folder back and open the src folder. Copy the glad.c file into the root directory of the project.
10. Finally to configure the Visual Studio project, go to Project -> ... Properties, then select platform to be "All Platforms", then go to VC++ Directories,
and for "Include Directories" point to your project's `Libraries/include/` folder. Then for "Library Directories" point to your project's `Libraries/lib/`
folder.
11. Then on the left again, click Linker -> Input, then for "Additional Dependencies" type on seperate lines, "glfw3.lib" and "opengl32.lib".
12. Last thing to do, is drag the glad.c folder from your project's directory into the Source Files folder on Visual Studio. Then create a main file,
by going to Source Files, right-click and add a cpp file, call it "Main.cpp".
