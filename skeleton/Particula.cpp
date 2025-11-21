#include "Particula.h"
#include <iostream>
using namespace physx;
extern PxMaterial* gMaterial;

//Particula
Particula::Particula(Vector3D Pos, Vector3D Vel, Vector3D Acel, Vector4 Color, ForceGenerator* GeneradorFuerzas, float Radius, float Damping, float Mass) {
	_pos = PxTransform({ Pos.X(), Pos.Y(), Pos.Z()});
	_vel = Vel;
	_acel = Acel;
	_damping = Damping;
	_radius = Radius;
	_mass = Mass;
	_generadorFuerzas = GeneradorFuerzas;

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
Particula::agregarFuerza(const Vector3D& Fuerza) { 
	_acumuladorFuerzas = _acumuladorFuerzas + Fuerza;
}

void 
Particula::integrarFuerzas(double t) {
	if (_inverseMass <= 0.0f)
		return;

	_generadorFuerzas->updateUnaFuerza(this, t);

	Vector3D aceleracion = _acumuladorFuerzas * _inverseMass;

	_vel = _vel + (aceleracion * t);
	_pos.p = _pos.p + PxVec3(_vel.X() * t, _vel.Y() * t, _vel.Z() * t);
	_vel = _vel * pow(_damping, t);
	//std::cout << "X: " << _pos.p.x << ", Y: " << _pos.p.y << ", Z: " << _pos.p.z << std::endl;
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

//Proyectil
Proyectil::Proyectil(ForceGenerator* Generador, int Type, const Vector3D& Pos, const Vector3D& Vel, float Mass,
	float Damping, float Radius, const Vector4& Color, bool Activo)
	: Particula(Pos, Vel, Vector3D(0.0f,0.0f,0.0f), Color, Generador, Radius, Damping, Mass)
	, _type(Type)
	, _posInicial(Pos)
	, _activo(Activo)
	, gravityScale(1.0f)
	, _masaReal(Mass)
{
}

Proyectil::~Proyectil()
{
}

void Proyectil::reiniciarPos()
{
	_pos.p = PxVec3(_posInicial.X(), _posInicial.Y(), _posInicial.Z());
	_vel = Vector3D(0, 0, 0);
	_acumuladorFuerzas = Vector3D(0, 0, 0);
	_activo = false;

	_mass = _masaReal;
	if (_mass > 0.0f)
		_inverseMass = 1.0f / _mass;
	gravityScale = 1.0f;
}

void Proyectil::integrarFuerzas(double t)
{
	if (!_activo)
		return;

	if (_inverseMass <= 0.0f)
		return;

	_generadorFuerzas->updateUnaFuerza(this, t);

	Vector3D acceleration = (_acumuladorFuerzas * _mass) * _inverseMass;

	_vel = _vel + acceleration * t;
	_pos.p = _pos.p + PxVec3(_vel.X() * t, _vel.Y() * t, _vel.Z() * t);
	_vel = _vel * pow(_damping, t);

	
	_acumuladorFuerzas = Vector3D(0.0f, 0.0f, 0.0f);
}

void Proyectil::escalarFisicas(float velocityScale)
{
	if (velocityScale <= 0.0f)
		return;
	if (_masaReal <= 0.0f)
		_masaReal = _mass;

	_vel = _vel * velocityScale;

	float k2 = velocityScale * velocityScale;
	_mass = _masaReal / k2;
	if (_mass > 0.0f)
		_inverseMass = 1.0f / _mass;

	gravityScale = k2;
}

void Proyectil::setMasa(float newMass)
{
	_mass = newMass;
	if (_mass > 0.0f)
		_inverseMass = 1.0f / _mass;
	else
		_inverseMass = 0.0f;
}