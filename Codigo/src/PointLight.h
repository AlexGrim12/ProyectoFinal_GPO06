#pragma once
#include "DirectionalLight.h"

class PointLight : public Light
{
public:
	PointLight() : Light(), position(0.0f), constant(1.0f), linear(0.0f), exponent(0.0f) {}
	PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity,
		GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat con, GLfloat lin, GLfloat exp)
		: Light(red, green, blue, aIntensity, dIntensity), position(xPos, yPos, zPos),
		constant(con), linear(lin), exponent(exp) {}

	glm::vec3 position;
	GLfloat constant, linear, exponent;
};
