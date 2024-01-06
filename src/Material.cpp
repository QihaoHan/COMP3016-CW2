/*
The Material class
This includes the use of the material's shader, the material's ambient (global light color), diffuse (diffuse texture), specular (specular texture),
shininess (calculating the exponential coefficient of specular reflected light intensity, the larger the specular reflected light is, the more concentrated it is)
*/

#include "Material.h"

Material::Material(Shader *_shader, glm::vec3 _ambient, unsigned int _diffuse, unsigned int _specular, float _shininess) :
	shader(_shader),
	ambient(_ambient),
	diffuse(_diffuse),
	specular(_specular),
	shininess(_shininess)
{}

Material::~Material() {}
