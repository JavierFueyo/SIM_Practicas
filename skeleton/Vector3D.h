#pragma once
#include <cmath>

class Vector3D
{
	float _x, _y, _z;

public:
	Vector3D(float x = 0.0f, float y = 0.0f, float z = 0.0f) : _x(x), _y(y), _z(z) {};

	float Modulo() {
		return sqrt((_x * _x) + (_y * _y) + (_z * _z));
	}

	void NormalizarVector() {
		float mod = Modulo();
		_x = (_x / mod);
		_y = (_y / mod);
		_z = (_z / mod);
	}

	float ProductoEscalar(Vector3D other) {
		float res = 0;
		res += (_x * other._x);
		res += (_y * other._y);
		res += (_z * other._z);
		return res;
	}
	
	Vector3D ProductoPorEscalar(float other) {
		Vector3D res;
		res._x = _x * other;
		res._y = _y * other;
		res._z = _z * other;
		return res;
	}

	Vector3D operator=(Vector3D other) {
		return Vector3D(other._x, other._y, other._z);
	}

	Vector3D operator+(Vector3D other) {
		return Vector3D(_x + other._x, _y + other._y, _z + other._z);
	}

	Vector3D operator-(Vector3D other) {
		return Vector3D(_x - other._x, _y - other._y, _z - other._z);
	}

	float operator*(Vector3D other) {
		return ProductoEscalar(other);
	}

	Vector3D operator*(float other) {
		return ProductoPorEscalar(other);
	}
};