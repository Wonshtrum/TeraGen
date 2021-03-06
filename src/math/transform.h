#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "core.h"
#include "vector.h"
#include "matrix.h"

class Transform {
	private:
		Vector3 m_translation;
		Vector3 m_rotation;
		Vector3 m_scale;
		Matrix4 m_transformMatrix;
	public:
		Transform();

		void calculate();

		Matrix4& getMatrix();
		float* getRawMatrix();

		Vector3& getTranslation();
		Vector3& getRotation();
		Vector3& getScale();

		void setTranslation(float x, float y, float z);
		void setTranslation(Vector3 translation);

		void setRotation(float x, float y, float z);
		void setRotation(Vector3 rotation);

		void setScale(float x, float y, float z);
		void setScale(Vector3 scale);

		friend std::ostream& operator<<(std::ostream& out, Transform& transform);
};

std::ostream& operator<<(std::ostream& out, Transform& transform);


#endif