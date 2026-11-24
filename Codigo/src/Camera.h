#pragma once
#include <glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

class Camera
{
public:
	Camera() : position(0.0f), front(0.0f, 0.0f, -1.0f), up(0.0f, 1.0f, 0.0f), right(1.0f, 0.0f, 0.0f),
		worldUp(0.0f, 1.0f, 0.0f), yaw(-90.0f), pitch(0.0f), moveSpeed(5.0f), turnSpeed(0.5f) {}
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch,
		GLfloat startMoveSpeed, GLfloat startTurnSpeed)
	{
		position = startPosition;
		worldUp = startUp;
		yaw = startYaw;
		pitch = startPitch;
		moveSpeed = startMoveSpeed;
		turnSpeed = startTurnSpeed;
		front = glm::vec3(0.0f, 0.0f, -1.0f);
		update();
	}

	glm::mat4 calculateViewMatrix() { return glm::lookAt(position, position + front, up); }
	glm::vec3 getCameraPosition() { return position; }
	glm::vec3 getCameraDirection() { return glm::normalize(front); }

private:
	glm::vec3 position, front, up, right, worldUp;
	GLfloat yaw, pitch, moveSpeed, turnSpeed;

	void update()
	{
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(front);
		right = glm::normalize(glm::cross(front, worldUp));
		up = glm::normalize(glm::cross(right, front));
	}
};
