#pragma once
#include "PointLight.h"

class SpotLight : public PointLight
{
public:
	SpotLight() : PointLight(), direction(0.0f, -1.0f, 0.0f), edge(0.0f), procEdge(1.0f) {}
	SpotLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity,
		GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat xDir, GLfloat yDir, GLfloat zDir,
		GLfloat con, GLfloat lin, GLfloat exp, GLfloat edg)
		: PointLight(red, green, blue, aIntensity, dIntensity, xPos, yPos, zPos, con, lin, exp)
	{
		direction = glm::normalize(glm::vec3(xDir, yDir, zDir));
		edge = edg;
		procEdge = cosf(glm::radians(edge));
	}

	void SetFlash(glm::vec3 pos, glm::vec3 dir)
	{
		position = pos;
		direction = glm::normalize(dir);
	}

	glm::vec3 direction;
	GLfloat edge, procEdge;
};
