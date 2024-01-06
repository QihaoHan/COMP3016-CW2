/*
LightPoint class
The light source, which needs to pay attention to the light source position, direction (determined by the three rotation angles when initialized) and color, is generally considered to decay with the square of distance
It also contains three coefficients of the attenuation function (quadratic function)
In addition, it is necessary to pay attention to the Angle from the center line of the light
*/

#include "LightSpot.h"

LightSpot::LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color) :
	position(_position),
	angles(_angles),
	color(_color)
{
	constant = 1.0f;
	linear = 0.1f;
	quadratic = 0.001f;
	UpdateDirection();
}

void LightSpot::UpdateDirection() {
	direction = glm::vec3(0.0f, 0.0f, 1.0f);	// pointing to z (forward)
	direction = glm::rotateZ(direction, angles.z);
	direction = glm::rotateX(direction, angles.x);
	direction = glm::rotateY(direction, angles.y);
	direction = -1.0f * direction;	//What you need to know in shader is the direction from the origin (the opposite direction)
}

LightSpot::~LightSpot() {}

