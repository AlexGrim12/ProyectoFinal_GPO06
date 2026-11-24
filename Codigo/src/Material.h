#pragma once
#include <glew.h>

class Material
{
public:
	Material() : specularIntensity(0.0f), shininess(0.0f) {}
	Material(GLfloat sIntensity, GLfloat shine) : specularIntensity(sIntensity), shininess(shine) {}

	void UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation)
	{
		glUniform1f(specularIntensityLocation, specularIntensity);
		glUniform1f(shininessLocation, shininess);
	}

private:
	GLfloat specularIntensity;
	GLfloat shininess;
};
