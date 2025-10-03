#include "Particula.h"
using namespace physx;
extern PxMaterial* gMaterial;

Particula::Particula(PxVec3 Pos, PxVec3 Vel, PxVec3 Acel, float Damping) {
	_pos = PxTransform({ Pos.x, Pos.y, Pos.z });
	_vel = Vel;
	_acel = Acel;
	_damping = Damping;

	PxSphereGeometry sphere(1.0f);
	renderItem = new RenderItem(CreateShape(sphere, gMaterial), &_pos, { 1, 1, 0, 1 });
}

void
Particula::integrarEuler(double t) {
	_pos.p = _pos.p + t * _vel;
	_vel = (_vel + _acel * t);
	_vel = _vel * pow(_damping, t);
}

void
Particula::integrarEulerSemiImplicito(double t) {
	_vel = (_vel + _acel * t);
	_vel = _vel * pow(_damping, t);
	_pos.p = _pos.p + t * _vel;
}

void
Particula::integrarVerlet(double t) {
	if (_counter == 0) {
		_previousPos = _pos.p;
		_vel = (_vel + _acel * t);
		_vel = _vel * pow(_damping, t);
		_pos.p = _pos.p + t * _vel;
	}
	else {
		_sigPos = 2 * _pos.p - _previousPos + (t * t * _acel);
		//_vel = (_sigPos - _previousPos) / (2 * t);
		_previousPos = _pos.p;
		_pos.p = _sigPos;
	}
	_counter++;
}