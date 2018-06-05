#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include "../core/Window.h"

class Transform
{

public:
	Transform(
		const glm::vec3& pos = glm::vec3(0.0f, 0.0f, 0.0f),
		const glm::quat& rot = glm::quat(0.0f, 0.0f, 0.0f, 1.0f),
		const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)
	);
	virtual ~Transform() {};

	bool hasChanged() const;

	void update();

	void setPos(const glm::vec3& pos);
	void setRot(const glm::quat& rot);
	void setScale(const glm::vec3& scale);

	Transform* getParent();
	void setParent(Transform* parent);

	//void rotate(const float& angle, const glm::vec3& axis);
	void rotate(const glm::vec3& axis, float angle);
	void rotate(glm::quat rotation);
	glm::vec3 rotate(glm::vec3 axis, glm::quat rotation);

	glm::vec3& getPos();
	glm::quat& getRot();
	glm::vec3& getScale();

	glm::vec3 getRight();
	glm::vec3 getLeft();
	glm::vec3 getUp();
	glm::vec3 getDown();
	glm::vec3 getForward();
	glm::vec3 getBackward();

	glm::vec3 getTransformedPos();
	glm::quat getTransformedRot();

	glm::mat4 getWorldMatrix() const;

private:
	glm::vec3 m_pos;
	glm::quat m_rot;
	glm::vec3 m_scale;

	glm::vec3 m_forward;

	mutable glm::mat4 m_parentMatrix;
	mutable glm::vec3 m_old_pos;
	mutable glm::quat m_old_rot;
	mutable glm::vec3 m_old_scale;

	Transform* m_parent;

	glm::quat mul(glm::quat q, glm::vec3 v);
	glm::mat4 translate(const glm::vec3& v) const;
	glm::mat4 scale(const glm::vec3&v) const;

};