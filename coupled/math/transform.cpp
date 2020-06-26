#include "vector.h"
#include "matrix.h"

class Transform {
	private:
		Vector3 m_translation;
		Vector3 m_rotation;
		Vector3 m_scale;
		Matrix4 m_transformMatrix;
	public:
		Transform() {
			m_translation = Vector3(0, 0, 0);
			m_rotation = Vector3(0, 0, 0);
			m_scale = Vector3(1, 1, 1);
			calculate();
		}

		void calculate() {
			Matrix4 translationMatrix = Matrix4().initTranslation(m_translation);
			Matrix4 rotationMatrix = Matrix4().initRotation(m_rotation);
			Matrix4 scaleMatrix = Matrix4().initScale(m_scale);
			m_transformMatrix = rotationMatrix*translationMatrix*scaleMatrix;
		}

		Matrix4& getMatrix() {
			return m_transformMatrix;
		}
		float* getRawMatrix() {
			return m_transformMatrix.m;
		}

		Vector3& getTranslation() { return m_translation; }
		Vector3& getRotation() { return m_rotation; }
		Vector3& getScale() { return m_scale; }

		void setTranslation(float x, float y, float z) {
			m_translation = Vector3(x, y, z);
		}
		void setTranslation(Vector3 translation) {
			m_translation = translation;
		}

		void setRotation(float x, float y, float z) {
			m_rotation = Vector3(x, y, z);
		}
		void setRotation(Vector3 rotation) {
			m_rotation = rotation;
		}

		void setScale(float x, float y, float z) {
			m_scale = Vector3(x, y, z);
		}
		void setScale(Vector3 scale) {
			m_scale = scale;
		}

		friend std::ostream& operator<<(std::ostream& out, Transform& transform);
};

std::ostream& operator<<(std::ostream& out, Transform& transform) {
	out << transform.m_transformMatrix;
	return out;
}
