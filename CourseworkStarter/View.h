#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct View
{
public:
	View()
	{

	};
	void initialiseCamera(const glm::vec3& pos, float fov, float aspect, float nearClip, float farClip)
	{
		this->position = pos;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projectionMat = glm::perspective(fov, aspect, nearClip, farClip);

	}

	inline glm::mat4 GetViewProjectionMatrix() const
	{
		return projectionMat * glm::lookAt(position, position + forward, up);
	}

	void MoveForward(float amount)
	{
		position += forward * amount;
	}

	void MoveBackwards(float amount)
	{
		position -= forward * amount;
	}

	void MoveRight(float amount)
	{
		position -= glm::cross(up, forward) * amount;
	}

	void MoveLeft(float amount)
	{
		position += glm::cross(up, forward) * amount;
	}

private:
	glm::mat4 projectionMat;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;

};