#pragma once
#include "Vector3D.h";
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include <cmath>
using namespace physx;

class Particula
{
public:
	Particula(Vector3D Pos, Vector3D Vel, Vector3D Acel, float Damping = 1);
	~Particula();

	void integrarEuler(double t);
	void integrarEulerSemiImplicito(double t);
	void integrarVerlet(double t);

	float getKineticEnergy() { return _mass * _vel.Modulo(); }
private:
	Vector3D _vel;
	Vector3D _acel;
	physx::PxTransform _pos;
	float _damping;
	int _counter = 0;
	Vector3D _previousPos;
	Vector3D _sigPos;

	RenderItem* renderItem;

	float _mass = 0;
	float _gravity = 0;
};