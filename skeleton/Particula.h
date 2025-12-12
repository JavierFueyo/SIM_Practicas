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
	virtual void integrarFuerzas(double t);

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
	float getRadius() { return _radius; }

	void agregarTipoFuerza(TipoFuerza* tF, bool Activa) {
		_generadorFuerzas->add(this, tF, Activa);
		if (tF->getTipo() == FUERZAS::GRAVEDAD) {
			_gravedad = tF->getGrav();
			_fuerzaGravedad = tF;
		}
	}
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
	TipoFuerza* _fuerzaGravedad;
	Vector3D _gravedad;
	Vector3D _acumuladorFuerzas;
	ForceGenerator* _generadorFuerzas;
};

enum gBalas { BALAPIEDRA = 0, BALADINAMITA = 1 };

class Proyectil : public Particula {
public:
	Proyectil(ForceGenerator* Generador,
		gBalas type,
		const Vector3D& pos = Vector3D(),
		const Vector3D& vel = Vector3D(),
		float mass = 1.0f,
		float damping = 0.99f,
		float radius = 0.1f,
		const Vector4& color = Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		bool Activo = false);

	virtual ~Proyectil();

	virtual void reiniciarPos();
	virtual void integrarFuerzas(double dt) override;
	virtual void escalarFisicas(float velocityScale);
	void setMasa(float newMass);
	float getMasaReal() const { return _mass; }
	float getScaledMass() const { return _masaEscalada; }
	bool estaActivo() const { return _activo; }
	void setActivo(bool value) { _activo = value; }

	gBalas getType() {
		return _type;
	}
protected:
	Vector3D _posAux;
	Vector3D _posInicial;
	bool _activo = true;
	Vector3D _gravedadEscalada = _gravedad;
	float _masaEscalada = _mass;
	gBalas _type;
};