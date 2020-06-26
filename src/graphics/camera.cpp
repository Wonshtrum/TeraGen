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
	std::cout << event.getKeyCode() << std::endl;
	float speed = 0.01;
	switch (event.getKeyCode()) {
		case 263:
			m_transform.getRotation().y -= speed;
			break;
		case 262:
			m_transform.getRotation().y += speed;
			break;
		case 265:
			m_transform.getRotation().x += speed;
			break;
		case 264:
			m_transform.getRotation().x -= speed;
			break;
	}
	m_transform.calculate();
	calculate();
	return false;
}
void Camera::onEvent(Event& event) {
	dispatch<KeyPressEvent>(event, M_BIND(Camera::onKeyEvent));
}
