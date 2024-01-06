/*
LightDirectional class
Parallel light source, light source position is meaningless, only need to pay attention to the direction (determined by the three rotation angles when initializing) and color, no attenuation
*/

#include "LightDirectional.h"

LightDirectional::LightDirectional(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color) :
	position(_position),
	angles(_angles),
	color(_color)
{
	UpdateDirection();
}

void LightDirectional::UpdateDirection() {
	direction = glm::vec3(0.0f, 0.0f, 1.0f);	// pointing to z (forward)
	direction = glm::rotateZ(direction, angles.z);
	direction = glm::rotateX(direction, angles.x);
	direction = glm::rotateY(direction, angles.y);
	direction = -1.0f * direction;	//What you need to know in shader is the direction from the origin (the opposite direction)
}

LightDirectional::~LightDirectional() {}
