#pragma once
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "Shader.h"

class Material
{
public:
	Shader *shader;
	glm::vec3 ambient;
	unsigned int diffuse;	
	//glm::vec3 diffuse;
	unsigned int specular;
	//glm::vec3 specular;
	float shininess;

	Material(Shader *_shader, glm::vec3 _ambient, unsigned int _diffuse, unsigned int _specular, float _shininess);
	~Material();
};

