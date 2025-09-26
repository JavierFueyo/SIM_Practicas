#include "Particula.h"
using namespace physx;
extern PxMaterial* gMaterial;

Particula::Particula(Vector3D Pos, Vector3D Vel, Vector3D Acel) {
	_pos = PxTransform({ Pos.X(), Pos.Y(), Pos.Z() });
	_vel = Vel;
	_acel = Acel;

	PxSphereGeometry sphere(1.0f);
	renderItem = new RenderItem(CreateShape(sphere, gMaterial), &_pos, { 1, 0, 0, 1 });
}

void
Particula::integrar(double t) {
	_vel = _vel + _acel * t;
	_pos.p = _pos.p + PxVec3(_vel.X(), _vel.Y(), _vel.Z()) * t;
}