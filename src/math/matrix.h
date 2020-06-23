#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>
#include <math.h>
#include "vector.h"
#define m(x, y) m[4*y+x]

struct Matrix4 {
	float m[4*4];
	Matrix4();

	Matrix4& initIdentity();

	Matrix4& initTranslation(float x, float y, float z);
	Matrix4& initTranslation(Vector3 tranlation);

	Matrix4& initRotation(float x, float y, float z);
	Matrix4& initRotation(Vector3 rotation);

	Matrix4& initScale(float x, float y, float z);
	Matrix4& initScale(Vector3 scale);

	Matrix4 operator*(Matrix4&& other);
	Matrix4 operator*(Matrix4& other);

	friend std::ostream& operator<<(std::ostream& out, Matrix4& matrix);
	friend std::ostream& operator<<(std::ostream& out, Matrix4&& matrix);
};

std::ostream& operator<<(std::ostream& out, Matrix4&& matrix);
std::ostream& operator<<(std::ostream& out, Matrix4& matrix);


#endif