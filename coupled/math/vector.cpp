struct Vector3 {
	float x;
	float y;
	float z;

	Vector3(): x(0), y(0), z(0) {}
	Vector3(float _x, float _y, float _z): x(_x), y(_y), z(_z) {}
};

std::ostream& operator<<(std::ostream& out, Vector3&& vector) {
	return out << "[" << vector.x << ", " << vector.y << ", " << vector.z << "]";
}
std::ostream& operator<<(std::ostream& out, Vector3& vector) {
	return out << (Vector3&&)vector;
}
