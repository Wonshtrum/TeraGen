#include "math/transform.h"

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
			std::cout << m_transform << std::endl;
			m_projectedTransformMatrix = m_projectionMatrix*m_transform.getMatrix();
		}

		Matrix4& getMatrix() {
			return m_projectedTransformMatrix;
		}

		Transform& getTransform() {
			return m_transform;
		}
};
