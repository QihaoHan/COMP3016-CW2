#pragma once

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <Windows.h>
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>
#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

#include <glm/glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Material.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"
#include "Mesh.h"
#include "Model.h"


#pragma region Model Data
// The displacement distance of 10 cubes from the original cube. We just change position here
glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 lightPositon[] = {
	glm::vec3(1.0f, 5.0f, -1.0f)
};

#pragma endregion

#pragma region Camera Declare

float cameraPosition[3] = { 0.0f, 0.0f, 5.0f };
float cameraTarget[3] = { 0.0f, 0.0f, 0.0f };
float cameraUp[3] = { 0.0f, -1.0f, 0.0f };
int lightOpenTag = 0;
//Initializes the camera object
//Camera camera(glm::vec3(cameraPosition[0], cameraPosition[1], cameraPosition[2]),
//			  glm::vec3(cameraTarget[0], cameraTarget[1], cameraTarget[2]),
//			  glm::vec3(cameraUp[0], cameraUp[1], cameraUp[2]));

Camera camera(glm::vec3(0.0f, 10.0f,5.0f), 49.49f, -3.2f, glm::vec3(0.5f, 0.5f, 0.5f));
#pragma endregion

#pragma region Light Declare
LightDirectional light(
	glm::vec3(1.0f, 1.0f, -1.0f), 
	glm::vec3(glm::radians(90.0f), glm::radians(0.0f), 0.0f), 
	glm::vec3(1.0f, 1.0f, 1.0f));

LightPoint lightP0(
	glm::vec3(1.0f, 0.0f, 0.0f),								//coordinate
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0.0f),	//angle
	glm::vec3(1.0f, 0.0f, 0.0f));								//colour
LightPoint lightP1(
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f));
LightPoint lightP2(
	glm::vec3(0.0f, 0.0f, 1.0f),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0.0f),
	glm::vec3(0.0f, 0.0f, 1.0f));
LightPoint lightP3(
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0.0f),
	glm::vec3(1.0f, 1.0f, 1.0f));

LightSpot lightS(
	glm::vec3(0.0f, 8.0f, 0.0f), 
	glm::vec3(glm::radians(90.0f), glm::radians(0.0f), 0.0f), //This direction is down
	glm::vec3(1.0f, 1.0f, 1.0f));
#pragma endregion

#pragma region Input Declare
void processInput(GLFWwindow *window) {		//Record keystroke events that occur
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		lightOpenTag = 1;
	}
	else if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		lightOpenTag = 0;
	}
}
#pragma endregion

unsigned int loadImageToGUP(const char *fileName, GLint internalFormat, GLenum format, int textureSlot) {
	//Read the image into the Texture buffer and bind it to TEXTURE_2D
	unsigned int TexBuffer;
	glGenTextures(1, &TexBuffer);
	glActiveTexture(GL_TEXTURE0 + textureSlot);		
	glBindTexture(GL_TEXTURE_2D, TexBuffer);

	// Load images via stb
	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);		
	unsigned char *data = stbi_load(fileName, &width, &height, &nrChannel, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		printf("Load image failed.\n");
	}
	stbi_image_free(data);

	return TexBuffer;
}

unsigned int loadImageToGUP4Name(const char* fileName, GLint internalFormat, GLenum format, int textureSlot) {
	// Read the image into the Texture buffer and bind it to TEXTURE_2D
	unsigned int TexBuffer;
	glGenTextures(1, &TexBuffer);
	glActiveTexture(GL_TEXTURE0 + textureSlot);	
	glBindTexture(GL_TEXTURE_2D, TexBuffer);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load images via stb
	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(false);		
	unsigned char* data = stbi_load(fileName, &width, &height, &nrChannel, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		printf("Load image failed.\n");
	}
	stbi_image_free(data);

	return TexBuffer;
}

int main(int argc, char *argv[]) {

	std::string exePath = argv[0];

#pragma region Open A Window
	//glfw library related initial configuration
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "Demo", nullptr, nullptr);	//col, row, title of the window
	if (window == nullptr) {
		printf("Open GLFW window failed.");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);	//Set as main window

	//Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		printf("Init GLEW failed.");
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);		//Control the area that can be drawn
	glEnable(GL_DEPTH_TEST);		//Enable z-buffer to save depth information

#pragma endregion

#pragma region Init Shader
	// Read the shader code
	Shader *myShader = new Shader(".\\src\\vertexSource.vert", ".\\src\\fragmentSource.frag");
	myShader->test();

	///// Flashlight for shader
	Shader* myShaderLightP = new Shader(".\\src\\shader.vs", ".\\src\\shader.fs");
#pragma endregion

#pragma region Init Material
	Material *myMaterial = new Material(
		myShader,
		glm::vec3(1.0f, 1.0f, 1.0f),
		loadImageToGUP(".\\src\\container2.png", GL_RGBA, GL_RGBA, Shader::DIFFUSE),
		loadImageToGUP(".\\src\\container2_specular.png", GL_RGBA, GL_RGBA, Shader::SPECULAR),
		128.0f
	);
	loadImageToGUP(".\\src\\fl.png", GL_RGB, GL_RGB, Shader::METAL);
	loadImageToGUP4Name(".\\src\\name.png", GL_RGBA, GL_RGBA, Shader::NAME);
	/*Material* myMaterialLightP = new Material(
		myShaderLightP,
		glm::vec3(1.0f, 1.0f, 1.0f),
		loadImageToGUP(".\\src\\metal.png", GL_RGB, GL_RGB, Shader::METAL),
		loadImageToGUP(".\\src\\metal.png", GL_RGB, GL_RGB, Shader::METAL),
		128.0f
	);*/
#pragma endregion

	//Mesh cube(vertices);
	Model model(".\\src\\cube.obj");

	// Import flashlight model
	Model modelLightP(".\\src\\lightP.obj");



#pragma region Prepare MVP matrices
	glm::mat4 modelMat;
	glm::mat4 modelMatLightP;
	glm::mat4 viewMat;
	glm::mat4 projMat;
	projMat = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.1f, 100.0f);


#pragma endregion

	while (!glfwWindowShouldClose(window)) {

		processInput(window);
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);					//The parameter is RGB+ opacity and ranges from 0 to 1
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//Clear the color information and z-buffer (depth information) of the previous frame before rendering the next frame

		viewMat = camera.GetViewMatrix();

		for (int i = 0; i < 1; i++) {
			// Set Model Matrixes
			modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);	//Parameter 1 is the identity matrix
			float angleCube = 20.0f;
			modelMat = glm::rotate(modelMat, (float)glfwGetTime() * glm::radians(angleCube), glm::vec3(1.0f, 1.0f, 1.0f));
			// Set Material -> Shader Program
			myShader->use();
			//The uniform of the passed coordinate transformation
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));

#pragma region Load Lights
			//Incoming coral-red light source
			glUniform3f(glGetUniformLocation(myShader->ID, "objColor"), 1.0f, 1.0f, 1.0f);
			glUniform3f(glGetUniformLocation(myShader->ID, "ambientColor"), 0.3f, 0.3f, 0.3f);	//Ambient light

			//The following section adds a parallel light source, four point light sources, and a concentrator
			
			//Uniform parameters required for parallel light sources
			glUniform3f(glGetUniformLocation(myShader->ID, "lightD.pos"), light.position.x, light.position.y, light.position.z);		//Light source location, point light source required
			glUniform3f(glGetUniformLocation(myShader->ID, "lightD.color"), light.color.x, light.color.y, light.color.z);				//Light source color
			glUniform3f(glGetUniformLocation(myShader->ID, "lightD.dirToLight"), light.direction.x, light.direction.y, light.direction.z);	//Direction of light source
			/**/
			//Uniform parameters required for point light source
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP0.pos"), lightP0.position.x, lightP0.position.y, lightP0.position.z);		
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP0.color"), lightP0.color.x, lightP0.color.y, lightP0.color.z);				
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP0.dirToLight"), lightP0.direction.x, lightP0.direction.y, lightP0.direction.z);	
			//Attenuation coefficient of point light source
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP0.constant"), lightP0.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP0.linear"), lightP0.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP0.quadratic"), lightP0.quadratic);

			
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP1.pos"), lightP1.position.x, lightP1.position.y, lightP1.position.z);		
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP1.color"), lightP1.color.x, lightP1.color.y, lightP1.color.z);				
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP1.dirToLight"), lightP1.direction.x, lightP1.direction.y, lightP1.direction.z);	
			
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP1.constant"), lightP1.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP1.linear"), lightP1.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP1.quadratic"), lightP1.quadratic);

			
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP2.pos"), lightP2.position.x, lightP2.position.y, lightP2.position.z);		
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP2.color"), lightP2.color.x, lightP2.color.y, lightP2.color.z);				
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP2.dirToLight"), lightP2.direction.x, lightP2.direction.y, lightP2.direction.z);	
			
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP2.constant"), lightP2.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP2.linear"), lightP2.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP2.quadratic"), lightP2.quadratic);

			
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP3.pos"), lightP3.position.x, lightP3.position.y, lightP3.position.z);		
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP3.color"), lightP3.color.x, lightP3.color.y, lightP3.color.z);				
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP3.dirToLight"), lightP3.direction.x, lightP3.direction.y, lightP3.direction.z);	
			
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP3.constant"), lightP3.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP3.linear"), lightP3.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP3.quadratic"), lightP3.quadratic);
			
			glUniform3f(glGetUniformLocation(myShader->ID, "lightS.pos"), lightS.position.x, lightS.position.y, lightS.position.z);		
			glUniform3f(glGetUniformLocation(myShader->ID, "lightS.color"), lightS.color.x, lightS.color.y, lightS.color.z);				
			glUniform3f(glGetUniformLocation(myShader->ID, "lightS.dirToLight"), lightS.direction.x, lightS.direction.y, lightS.direction.z);	
			
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.constant"), lightS.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.linear"), lightS.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.quadratic"), lightS.quadratic);
			
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.cosPhyInner"), lightS.cosPhyInner);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.cosPhyOuter"), lightS.cosPhyOuter);
#pragma endregion

#pragma region Load material
			glUniform3f(glGetUniformLocation(myShader->ID, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);
			//Material ball
			myMaterial->shader->SetUniform3f("material.ambient", myMaterial->ambient);
			//myMaterial->shader->SetUniform3f("material.diffuse", myMaterial->diffuse);
			myMaterial->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
			//myMaterial->shader->SetUniform3f("material.specular", myMaterial->specular);
			myMaterial->shader->SetUniform1i("material.specular", Shader::SPECULAR);

			if (lightOpenTag) {
				myMaterial->shader->SetUniform1f("material.shininess", myMaterial->shininess);
			}
			else {
				myMaterial->shader->SetUniform1f("material.shininess", 0.0f);
			}
			
			model.Draw(myMaterial->shader);
#pragma endregion

			myShaderLightP->use();
			// Set Model Matrixes
			modelMatLightP = glm::translate(glm::mat4(1.0f), lightPositon[i]);	// Parameter 1 is the identity matrix
			modelMatLightP = glm::scale(modelMatLightP, glm::vec3(0.005f));

			float angle = 20.0f;
			modelMatLightP = glm::rotate(modelMatLightP, 4.8f * glm::radians(angle), glm::vec3(1.0f, 1.0f, 1.0f));
			modelMatLightP = glm::rotate(modelMatLightP, -(float)glfwGetTime() * glm::radians(angle), glm::vec3(0.3f, 0.0f, 0.0f));

			glUniformMatrix4fv(glGetUniformLocation(myShaderLightP->ID, "model"), 1, GL_FALSE, glm::value_ptr(modelMatLightP));
			glUniformMatrix4fv(glGetUniformLocation(myShaderLightP->ID, "view"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(myShaderLightP->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projMat));
			glUniform1i(glGetUniformLocation(myShaderLightP->ID, "ourTexture1"), Shader::METAL); 
			glUniform1i(glGetUniformLocation(myShaderLightP->ID, "ourTexture2"), Shader::NAME);
			modelLightP.Draw(myShaderLightP);

		}

		glfwSwapBuffers(window);		//Swap two color staging blocks (each pixel has two color staging blocks)
		glfwPollEvents();				//Get the user's keys (actions)
		
		camera.UpdateCameraPosition();	
	}
	glfwTerminate();		
	return 0;
}
