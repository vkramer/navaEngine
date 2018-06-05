#pragma once

#include "../Component.h"

#include <glm/glm.hpp>

class Camera : public Component {

public:
	Camera(float fov, float aspect, float zNear, float zFar);
	~Camera() {};

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewProjectionMatrix();

	void input(float delta);

	virtual void addToRenderingEngine(RenderingEngine* renderingEngine);

private:
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	glm::vec2 center;
	float m_sensitivity;

	float m_fov;
	float m_aspect;
	float m_zNear;
	float m_zFar;

	float yaw;
	float pitch;
	float fov;

};