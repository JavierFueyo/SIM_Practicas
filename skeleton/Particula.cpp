#include "Particula.h"
#include <iostream>
using namespace physx;
extern PxMaterial* gMaterial;

Particula::Particula(Vector3D Pos, Vector3D Vel, Vector3D Acel, float Damping, float Mass, float Gravity) {
	_pos = PxTransform({ Pos.X(), Pos.Y(), Pos.Z()});
	_vel = Vel;
	_acel = Vector3D(Acel.X(), -Gravity, Acel.Z());
	_damping = Damping;
	_mass = Mass;
	_gravity = Gravity;

	PxSphereGeometry sphere(1.0f);
	renderItem = new RenderItem(CreateShape(sphere, gMaterial), &_pos, { 1, 1, 0, 1 });
}
Particula::~Particula() {
	//delete renderItem;
}

void
Particula::integrarEuler(double t) {
	_pos.p.x = _pos.p.x + t * _vel.X();
	_pos.p.y = _pos.p.y + t * _vel.Y();
	_pos.p.z = _pos.p.z + t * _vel.Z();
	_vel = (_vel + _acel * t);
	_vel = _vel * pow(_damping, t);
	_timeAlive += t;
}

void
Particula::integrarEulerSemiImplicito(double t) {
	_vel = (_vel + _acel * t);
	_vel = _vel * pow(_damping, t);
	_pos.p.x = _pos.p.x + t * _vel.X();
	_pos.p.y = _pos.p.y + t * _vel.Y();
	_pos.p.z = _pos.p.z + t * _vel.Z();
	_timeAlive += t;
}

void
Particula::integrarVerlet(double t) {
	/*
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
	_timeAlive += t;
	*/
}