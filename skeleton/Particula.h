#pragma once
#include "Vector3D.h";
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
using namespace physx;

class Particula
{
public:
	Particula(Vector3D Pos, Vector3D Vel, Vector3D Acel);
	~Particula();

	void integrar(double t);

private:
	Vector3D _vel;
	Vector3D _acel;
	physx::PxTransform _pos;
	RenderItem* renderItem;
};