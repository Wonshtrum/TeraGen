#include "matrix.h"

Matrix4::Matrix4() {
	m(0, 0) = 0; m(1, 0) = 0; m(2, 0) = 0; m(3, 0) = 0;
	m(0, 1) = 0; m(1, 1) = 0; m(2, 1) = 0; m(3, 1) = 0;
	m(0, 2) = 0; m(1, 2) = 0; m(2, 2) = 0; m(3, 2) = 0;
	m(0, 3) = 0; m(1, 3) = 0; m(2, 3) = 0; m(3, 3) = 0;
}

Matrix4& Matrix4::initIdentity() {
	m(0, 0) = 1; m(1, 0) = 0; m(2, 0) = 0; m(3, 0) = 0;
	m(0, 1) = 0; m(1, 1) = 1; m(2, 1) = 0; m(3, 1) = 0;
	m(0, 2) = 0; m(1, 2) = 0; m(2, 2) = 1; m(3, 2) = 0;
	m(0, 3) = 0; m(1, 3) = 0; m(2, 3) = 0; m(3, 3) = 1;
	return *this;
}

Matrix4& Matrix4::initTranslation(float x, float y, float z) {
	m(0, 0) = 1; m(1, 0) = 0; m(2, 0) = 0; m(3, 0) = x;
	m(0, 1) = 0; m(1, 1) = 1; m(2, 1) = 0; m(3, 1) = y;
	m(0, 2) = 0; m(1, 2) = 0; m(2, 2) = 1; m(3, 2) = z;
	m(0, 3) = 0; m(1, 3) = 0; m(2, 3) = 0; m(3, 3) = 1;
	return *this;
}
Matrix4& Matrix4::initTranslation(Vector3 tranlation) {
	return initTranslation(tranlation.x, tranlation.y, tranlation.z);
}

Matrix4& Matrix4::initRotation(float x, float y, float z) {
	float sx = sin(x);
	float sy = sin(y);
	float sz = sin(z);
	float cx = cos(x);
	float cy = cos(y);
	float cz = cos(z);
	Matrix4 rx = Matrix4().initIdentity();
	Matrix4 ry = Matrix4().initIdentity();
	Matrix4 rz = Matrix4().initIdentity();

	rx.m(0, 0) = cz;
	rx.m(1, 0) = -sz;
	rx.m(0, 1) = sz;
	rx.m(1, 1) = cz;

	ry.m(1, 1) = cx;
	ry.m(2, 1) = -sx;
	ry.m(1, 2) = sx;
	ry.m(2, 2) = cx;

	rx.m(0, 0) = cy;
	rx.m(2, 0) = -sy;
	rx.m(0, 2) = sy;
	rx.m(2, 2) = cy;
	
	*this = rx*ry*rz;
	return *this;
}
Matrix4& Matrix4::initRotation(Vector3 rotation) {
	return initRotation(rotation.x, rotation.y, rotation.z);
}

Matrix4& Matrix4::initScale(float x, float y, float z) {
	m(0, 0) = x; m(1, 0) = 0; m(2, 0) = 0; m(3, 0) = 0;
	m(0, 1) = 0; m(1, 1) = y; m(2, 1) = 0; m(3, 1) = 0;
	m(0, 2) = 0; m(1, 2) = 0; m(2, 2) = z; m(3, 2) = 0;
	m(0, 3) = 0; m(1, 3) = 0; m(2, 3) = 0; m(3, 3) = 1;
	return *this;
}
Matrix4& Matrix4::initScale(Vector3 scale) {
	return initScale(scale.x, scale.y, scale.z);
}

Matrix4& Matrix4::initProjection(float fov, float width, float height, float zN, float zF) {
	float tfov = tan(fov/2);
	float ar = width/height;
	float zR = zN - zF;
	m(0, 0) = 1/(ar*tfov);	m(1, 0) = 0;		m(2, 0) = 0;		m(3, 0) = 0;
	m(0, 1) = 0; 		m(1, 1) = 1/tfov;	m(2, 1) = 0;		m(3, 1) = 0;
	m(0, 2) = 0; 		m(1, 2) = 0;		m(2, 2) = (-zN-zF)/zR;	m(3, 2) = 2*zF*zN/zR;
	m(0, 3) = 0; 		m(1, 3) = 0;		m(2, 3) = 1;		m(3, 3) = 0;
	return *this;
}

Matrix4 Matrix4::operator*(Matrix4&& other) {
	Matrix4 result;
	for (int i = 0 ; i < 4 ; i++) {
		for (int j = 0 ; j < 4 ; j++) {
			result.m(j, i) = m(0, i)*other.m(j, 0)+
					m(1, i)*other.m(j, 1)+
					m(2, i)*other.m(j, 2)+
					m(3, i)*other.m(j, 3);
		}
	}
	return result;
}
Matrix4 Matrix4::operator*(Matrix4& other) {
	return *this * (Matrix4&&)other;
}

std::ostream& operator<<(std::ostream& out, Matrix4&& matrix) {
	for (int y = 0 ; y < 4 ; y++) {
		for (int x = 0 ; x < 4 ; x++) {
			out << matrix.m(x, y) << " ";
		}
		out << std::endl;
	}
	return out;
}
std::ostream& operator<<(std::ostream& out, Matrix4& matrix) {
	return out << (Matrix4&&)matrix;
}
