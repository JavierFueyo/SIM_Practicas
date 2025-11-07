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

	Vector3D NormalizarVector() {
		float mod = Modulo();

		return Vector3D(_x / mod, _y / mod, _z / mod);
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

	Vector3D& operator=(const Vector3D &other) {
		_x = other._x;
		_y = other._y;
		_z = other._z;

		return *this;
	}

	Vector3D operator+(const Vector3D &other) {
		return Vector3D(_x + other._x, _y + other._y, _z + other._z);
	}

	Vector3D operator-(const Vector3D &other) {
		return Vector3D(_x - other._x, _y - other._y, _z - other._z);
	}

	float operator*(const Vector3D &other) {
		return ProductoEscalar(other);
	}

	Vector3D operator*(const float &other) {
		return ProductoPorEscalar(other);
	}

	Vector3D operator/(const float &other) {
		Vector3D res;
		res._x = _x / other;
		res._y = _y / other;
		res._z = _z / other;
		return res;
	}

	float X() {
		return _x;
	}
	float Y() {
		return _y;
	}
	float Z() {
		return _z;
	}
};