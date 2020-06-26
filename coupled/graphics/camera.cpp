#include "math/transform.h"
#include "events/events.h"
#include "macros.h"

class Camera {
	private:
		float m_fov;
		float m_width;
		float m_height;
		float m_zNear;
		float m_zFar;
		Transform m_transform;
		Matrix4 m_projectionMatrix;
		Matrix4 m_projectedTransformMatrix;

	public:
		Camera(float fov, float width, float height, float zNear, float zFar): m_fov(fov), m_width(width), m_height(height), m_zNear(zNear), m_zFar(zFar) {
				m_projectionMatrix = Matrix4().initProjection(fov, width, height, zNear, zFar);
		}
		
		void calculate() {
			m_projectedTransformMatrix = m_projectionMatrix*m_transform.getMatrix();
		}

		Matrix4& getMatrix() {
			return m_projectedTransformMatrix;
		}

		Transform& getTransform() {
			return m_transform;
		}

		bool onKeyEvent(KeyPressEvent& event) {
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
		void onEvent(Event& event) {
			dispatch<KeyPressEvent>(event, M_BIND(Camera::onKeyEvent));
		}
};
