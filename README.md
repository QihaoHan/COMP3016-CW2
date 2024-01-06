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
Import libraries and definitions: The program first imports OpenGL, GLFW, and other required libraries and header files.<br/>
Initialize GLFW: Initialize GLFW and set the OpenGL version and configuration by calling `glfwInit` and related functions.<br/>
Create window: Create a window with `glfwCreateWindow` and set it to be the primary context of the current thread.<br/>
Initialize GLEW: Initializes GLEW (a function pointer used to manage OpenGL) to use OpenGL functionality.<br/>
