#ifndef __CAMERA_H__
#define __CAMERA_H__

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
		Camera(float fov, float width, float height, float zNear, float zFar);

		void calculate();

		Matrix4& getMatrix();

		Transform& getTransform();
};


#endif