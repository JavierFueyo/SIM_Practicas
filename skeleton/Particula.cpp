#include "Particula.h"
#include <iostream>
using namespace physx;
extern PxMaterial* gMaterial;

Particula::Particula(Vector3D Pos, Vector3D Vel, Vector3D Acel, Vector4 Color, float Radius, float Damping, float Mass) {
	_pos = PxTransform({ Pos.X(), Pos.Y(), Pos.Z()});
	_vel = Vel;
	_acel = Acel;
	_damping = Damping;
	_radius = Radius;
	_mass = Mass;

	if (Mass > 0.0f) {
		_inverseMass = 1.0f / Mass;
	}
	else {
		_inverseMass = 0.0f;
	}

	PxSphereGeometry sphere(_radius);
	renderItem = new RenderItem(CreateShape(sphere, gMaterial), &_pos, Color);
}

Particula::~Particula() {
	if (renderItem != nullptr) {
		DeregisterRenderItem(renderItem);
		delete renderItem;
	}
}

void 
Particula::integrarFuerzas(double t) {
	if (_inverseMass <= 0.0f)
		return;


	Vector3D aceleracion = _acumuladorFuerzas * _inverseMass;

	_vel = _vel + (aceleracion * t);
	_pos.p = _pos.p + PxVec3(_vel.X() * t, _vel.Y() * t, _vel.Z() * t);
	_vel = _vel * pow(_damping, t);

	_acumuladorFuerzas = Vector3D(0.0f, 0.0f, 0.0f);
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