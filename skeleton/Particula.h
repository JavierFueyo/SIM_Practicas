#pragma once
#include "Vector3D.h";
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
using namespace physx;

class Particula
{
public:
	Particula(PxVec3 Pos, PxVec3 Vel, PxVec3 Acel);
	~Particula();

	void integrar(double t);

private:
	PxVec3 _vel;
	PxVec3 _acel;
	physx::PxTransform _pos;
	RenderItem* renderItem;
};