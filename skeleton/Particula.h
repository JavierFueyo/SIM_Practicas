#pragma once
#include "Vector3D.h";
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include <cmath>
using namespace physx;

class Particula
{
public:
	Particula(PxVec3 Pos, PxVec3 Vel, PxVec3 Acel, float Damping = 1);
	~Particula();

	void integrarEuler(double t);
	void integrarEulerSemiImplicito(double t);
	void integrarVerlet(double t);

private:
	PxVec3 _vel;
	PxVec3 _acel;
	physx::PxTransform _pos;
	float _damping;
	int _counter = 0;
	PxVec3 _previousPos;
	PxVec3 _sigPos;

	RenderItem* renderItem;
};