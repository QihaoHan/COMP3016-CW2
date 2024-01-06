/*
LightPoint class
Point light source, it is necessary to pay attention to the position and color of the light source, the direction is meaningless, and it is generally believed that the square decay with the distance
It also contains three coefficients of the attenuation function (quadratic function)
*/

#include "LightPoint.h"

LightPoint::LightPoint(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color):
	position(_position),
	angles(_angles),
	color(_color) 
{
	constant = 1.0f;
	linear = 0.1f;
	quadratic = 0.001f;
}

LightPoint::~LightPoint() {}
