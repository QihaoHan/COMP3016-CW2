# COMP3016/CW2

# Introduction
This project is called flashlight. Create a 3D rendering environment through OpenGL and CLFW libraries, showing how to load and render 3D models, handle lighting and materials, and use shaders to control rendering effects. The keyboard event controls the flashlight light source switch to complete the interaction.

# How to do open and control prototype
Open:<br/>
1. Decompress CW2.zip.
2. Open the "CW2" folder and continue to click on the "Project3" folder.
3. Move the "OpenGL" folder to "C:\Users\Public".
4. Run the "Project3.exe" file<br/>

Control:<br/>
Interact with the keyboard<br/>
O: Turn on flashlight light source<br/>
F: Turn off flashlight light source

# How does the program code work
**Initialize and configure the system**:<br/>
- Import libraries and definitions: The program first imports OpenGL, GLFW, and other required libraries and header files.<br/>
- Initialize GLFW: Initialize GLFW and set the OpenGL version and configuration by calling `glfwInit` and related functions.<br/>
- Create window: Create a window with `glfwCreateWindow` and set it to be the primary context of the current thread.<br/>
- Initialize GLEW: Initializes GLEW (a function pointer used to manage OpenGL) to use OpenGL functionality.<br/>

**Setting up the rendering environment**:<br/>
- Set Viewport: Define the size of the render window through the `glViewport`.<br>
- Enable depth testing: Use `glEnable(GL_DEPTH_TEST)` to ensure that objects are rendered correctly in 3D space.<br/>

**Load shaders and resource**:<br/>
- Load Shader: Create `shader` objects for subsequent rendering shader processing.<br/>
- Load materials and textures: Use the `loadImageToGUP` function to load image textures to the GPU for material creation.<br/>
- Create light objects: Create `LightDirectional`, `LightPoint`, `LightSpot`, etc. objects that simulate different lighting effects.<br/>

**Ready render loop**:<br/>
- Model loading: Create `Model` objects and load 3D model data.<br/>
- Set up the MVP matrix: Configure the Model, View, and Projection matrices to render 3D objects correctly.

**Render loop**:<br/>
- Event handling: Window and keyboard events are handled through the `processInput` function.<br/>
- Clean the screen: Clear the color and depth buffers.<br/>
- Update Camera view: Update the `Camera` object to reflect changes in the user's perspective.<br/>
- Model rendering:<br/>
Set the MVP matrix for each model.<br/>
Apply the shader program.<br/>
Information such as lighting and material is passed to the shader.<br/>
Call `model.draw` to Draw the 3D Model.<br/>

**End cleanup**:<br/>
- End the render loop: Exit the render loop when `glfwWindowShouldClose` returns `true`.<br/>
- Resource release: Releases allocated resources, such as texture and shader objects.<br/>
- Shut down GLFW: Use `glfwTerminate` to end the program, shut down GLFW and clean up allocated resources.<br/>
