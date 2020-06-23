#include "transform.h"

Transform::Transform() {}

void Transform::calculateTransformMatrix() {
	Matrix4 translationMatrix = Matrix4().initTranslation(m_translation);
	Matrix4 rotationMatrix = Matrix4().initRotation(m_rotation);
	Matrix4 scaleMatrix = Matrix4().initScale(m_scale);
	m_transformMatrix = translationMatrix*rotationMatrix*scaleMatrix;
}

Matrix4 Transform::getMatrix() {
	return m_transformMatrix;
}

void Transform::setTranslation(float x, float y, float z) {
	m_translation = Vector3(x, y, z);
}
void Transform::setTranslation(Vector3 translation) {
	m_translation = translation;
}

void Transform::setRotation(float x, float y, float z) {
	m_rotation = Vector3(x, y, z);
}
void Transform::setRotation(Vector3 rotation) {
	m_rotation = rotation;
}

void Transform::setScale(float x, float y, float z) {
	m_scale = Vector3(x, y, z);
}
void Transform::setScale(Vector3 scale) {
	m_scale = scale;
}

std::ostream& operator<<(std::ostream& out, Transform& transform) {
	out << transform.m_transformMatrix;
	return out;
}
