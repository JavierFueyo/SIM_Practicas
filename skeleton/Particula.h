#pragma once
#include "Vector3D.h";
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include "ForceGenerator.h"
#include <cmath>
using namespace physx;

class Particula
{
public:
	Particula(Vector3D Pos, Vector3D Vel, Vector3D Acel,  Vector4 Color, ForceGenerator* GeneradorFuerzas, float Radius = 1.0f, float Damping = 1.0f, float Mass = 0.0f);
	~Particula();

	void agregarFuerza(const Vector3D& Fuerza);
	void integrarFuerzas(double t);

	void integrarEuler(double t);
	void integrarEulerSemiImplicito(double t);
	void integrarVerlet(double t);

	PxTransform getPos() { return _pos; }
	float getTimeAlive() { return _timeAlive; }
	float getMass() { return _mass; }
	Vector3D getVel() { return _vel; }
	float getInverseMass() { return _inverseMass; }
	float getKineticEnergy() { return _mass * _vel.Modulo(); }
	ForceGenerator* getForceGenerator() { return _generadorFuerzas; }

	void agregarTipoFuerza(TipoFuerza* tF, bool Activa) { _generadorFuerzas->add(this, tF, Activa); }
	void quitarTipoFuerza(TipoFuerza* tF) { _generadorFuerzas->quitar(this, tF); }
protected:
	float _radius;
	Vector3D _vel;
	Vector3D _acel;
	PxTransform _pos;
	float _damping;
	int _counter = 0; //Verlet
	Vector3D _previousPos;
	Vector3D _sigPos;

	double _timeAlive = 0;

	RenderItem* renderItem;

	float _mass, _inverseMass;
	Vector3D _acumuladorFuerzas;
	ForceGenerator* _generadorFuerzas;
};

class Proyectil : public Particula {
	Proyectil(Vector3D Pos, Vector3D Vel, Vector3D Acel, Vector4 Color, float Radius = 1.0f, float Damping = 1.0f, float Mass = 0.0f);
};