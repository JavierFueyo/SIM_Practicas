#include "Particula.h"
using namespace physx;
extern PxMaterial* gMaterial;

Particula::Particula(PxVec3 Pos, PxVec3 Vel, PxVec3 Acel) {
	_pos = PxTransform({ Pos.x, Pos.y, Pos.z });
	_vel = Vel;
	_acel = Acel;

	PxSphereGeometry sphere(1.0f);
	renderItem = new RenderItem(CreateShape(sphere, gMaterial), &_pos, { 1, 1, 0, 1 });
}

void
Particula::integrar(double t) {
	_vel = _vel + _acel * t;
	_pos.p = _pos.p + _vel * t;
}