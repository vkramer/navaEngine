#include "Transform.h"

glm::vec3 transform(glm::mat4 m, glm::vec3 r);

Transform::Transform(const glm::vec3& pos, const glm::quat& rot, const glm::vec3& scale) :
	m_pos(pos),
	m_rot(rot),
	m_scale(scale),
	m_parent(nullptr)
{
	// Transform Constructor utilizing Quaternion Rotation
}

bool Transform::hasChanged() const {
	if (m_parent && m_parent->hasChanged())
		return true;

	if (m_pos != m_old_pos || m_rot != m_old_rot || m_scale != m_old_scale)
		return true;

	return false;
}

void Transform::update() {
	if (hasChanged()) {
		m_old_pos = m_pos;
		m_old_rot = m_rot;
		m_old_scale = m_scale;

		if (m_parent)
			m_parentMatrix = m_parent->getWorldMatrix();
	}
}

glm::mat4 Transform::getWorldMatrix() const {
	glm::mat4 posMatrix = translate(m_pos);
	glm::mat4 scaleMatrix = scale(m_scale);
	glm::mat4 rotMatrix = glm::mat4_cast(glm::normalize(m_rot));

	return m_parentMatrix * posMatrix * rotMatrix * scaleMatrix;
}

glm::vec3 Transform::getTransformedPos() {
	return transform(m_parentMatrix, m_pos);
}

glm::quat Transform::getTransformedRot() {
	glm::quat parentRot = glm::quat(0, 0, 0, 1);

	if (m_parent != nullptr)
		parentRot = m_parent->getTransformedRot();
	return parentRot * getRot();
}

glm::quat Transform::mul(glm::quat q, glm::vec3 v) {
	float w = -q.x * v.x - q.y * v.y - q.z * v.z;
	float x = q.w * v.x + q.y * v.z - q.z * v.y;
	float y = q.w * v.y + q.z * v.x - q.x * v.z;
	float z = q.w * v.z + q.x * v.y - q.y * v.x;

	return glm::quat(w, x, y, x);
}

glm::mat4 Transform::translate(const glm::vec3& v) const {
	glm::mat4 m;

	for (unsigned int i = 0; i < 4; i++)
		for (unsigned int j = 0; j < 4; j++)
			if (i == 3 && j != 3)
				m[i][j] = v[j];

	return m;
}

glm::mat4 Transform::scale(const glm::vec3& v) const {
	glm::mat4 m;

	for (unsigned int i = 0; i < 3; i++)
		for (unsigned int j = 0; j < 3; j++)
			if (i == j && i != 3)
				m[i][j] = v[i];

	return m;
}

void Transform::rotate(const glm::vec3& axis, float angle) {
	rotate(glm::angleAxis(angle, axis));
}

void Transform::rotate(glm::quat rotation) {
	m_rot = glm::normalize(rotation * m_rot);
}

glm::vec3 Transform::rotate(glm::vec3 axis, glm::quat rotation) {
	glm::quat _q = glm::conjugate(rotation);
	glm::quat w = rotation * glm::quat(0, axis) * _q;

	return glm::normalize(glm::vec3(w[0], w[1], w[2]));
}

glm::vec3& Transform::getPos()
{
	return m_pos;
}

glm::quat & Transform::getRot()
{
	return m_rot;
}

glm::vec3 & Transform::getScale()
{
	return m_scale;
}

Transform* Transform::getParent()
{
	return m_parent;
}

void Transform::setPos(const glm::vec3 & pos)
{
	m_pos = pos;
}

void Transform::setRot(const glm::quat & rot)
{
	m_rot = rot;
}

void Transform::setScale(const glm::vec3 & scale)
{
	m_scale = scale;
}

void Transform::setParent(Transform* parent)
{
	m_parent = parent;
}

glm::vec3 Transform::getForward()
{
	return rotate(glm::vec3(0, 0, 1), m_rot);
}

glm::vec3 Transform::getBackward()
{
	return rotate(glm::vec3(0, 0, -1), m_rot);
}

glm::vec3 Transform::getUp()
{
	return rotate(glm::vec3(0, 1, 0), m_rot);
}

glm::vec3 Transform::getDown()
{
	return rotate(glm::vec3(0, -1, 0), m_rot);
}

glm::vec3 Transform::getRight()
{
	return rotate(glm::vec3(-1, 0, 0), m_rot);
}

glm::vec3 Transform::getLeft()
{
	return rotate(glm::vec3(1, 0, 0), m_rot);
}

// HELPER FUNCTIONS
// ---------------------------------------------------------------------------------------------
glm::vec3 transform(glm::mat4 m, glm::vec3 r) {
	return glm::vec3(
		m[0][0] * r.x + m[0][1] * r.y + m[0][2] * r.z + m[0][3],
		m[1][0] * r.x + m[1][1] * r.y + m[1][2] * r.z + m[1][3],
		m[2][0] * r.x + m[2][1] * r.y + m[2][2] * r.z + m[2][3]
	);
}
