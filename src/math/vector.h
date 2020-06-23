#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <iostream>

struct Vector3 {
	float x;
	float y;
	float z;

	Vector3();
	Vector3(float _x, float _y, float _z);
};

std::ostream& operator<<(std::ostream& out, Vector3&& vector);
std::ostream& operator<<(std::ostream& out, Vector3& vector);


#endif