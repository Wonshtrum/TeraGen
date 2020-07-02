#include "camera.h"


Camera::Camera(float fov, float width, float height, float zNear, float zFar): m_fov(fov), m_width(width), m_height(height), m_zNear(zNear), m_zFar(zFar) {
	m_projectionMatrix = Matrix4().initProjection(fov, width, height, zNear, zFar);
}

void Camera::calculate() {
	m_projectedTransformMatrix = m_projectionMatrix*m_transform.getMatrix();
}

Matrix4& Camera::getMatrix() {
	return m_projectedTransformMatrix;
}

Transform& Camera::getTransform() {
	return m_transform;
}

bool Camera::onKeyEvent(KeyPressEvent& event) {
	//APP_TRACE(event.getKeyCode());
	return true;
}
bool Camera::onResizeEvent(WindowResizeEvent& event) {
	m_width = event.getWidth();
	m_height = event.getHeight();
	m_projectionMatrix.initProjection(m_fov, m_width, m_height, m_zNear, m_zFar);
	calculate();
	glViewport(0, 0, m_width, m_height);
	return true;
}
void Camera::onEvent(Event& event) {
	dispatch<KeyPressEvent>(event, M_BIND(Camera::onKeyEvent));
	dispatch<WindowResizeEvent>(event, M_BIND(Camera::onResizeEvent));
}
