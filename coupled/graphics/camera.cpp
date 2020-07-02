#include <GL/glew.h>
#include "math/transform.h"
#include "event/event.h"

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
			//APP_TRACE(event.getKeyCode());
			return true;
		}
		bool onResizeEvent(WindowResizeEvent& event) {
			m_width = event.getWidth();
			m_height = event.getHeight();
			m_projectionMatrix.initProjection(m_fov, m_width, m_height, m_zNear, m_zFar);
			calculate();
			glViewport(0, 0, m_width, m_height);
			return true;
		}
		void onEvent(Event& event) {
			dispatch<KeyPressEvent>(event, M_BIND(Camera::onKeyEvent));
			dispatch<WindowResizeEvent>(event, M_BIND(Camera::onResizeEvent));
		}
};
