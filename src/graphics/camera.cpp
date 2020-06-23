#include "camera.h"


Camera::Camera(float fov, float width, float height, float zNear, float zFar): m_fov(fov), m_width(width), m_height(height), m_zNear(zNear), m_zFar(zFar) {
		m_projectionMatrix = Matrix4().initProjection(fov, width, height, zNear, zFar);
}

void Camera::calculate() {
	std::cout << m_transform << std::endl;
	m_projectedTransformMatrix = m_projectionMatrix*m_transform.getMatrix();
}

Matrix4& Camera::getMatrix() {
	return m_projectedTransformMatrix;
}

Transform& Camera::getTransform() {
	return m_transform;
}
