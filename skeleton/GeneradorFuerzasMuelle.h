#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class GeneradorFuerzasMuelle : public TipoFuerza {
public:
	GeneradorFuerzasMuelle(double k, double LargoEnReposo, Particula* p) : _k(k), _largoEnReposo(LargoEnReposo), _p(p) {}

	virtual void updateFuerza(Particula* p, double t) override {
		PxVec3 posRel = p->getPos().p - _p->getPos().p;
		Vector3D PosicionRelativa = Vector3D(posRel.x, posRel.y, posRel.z);

		const float largo = PosicionRelativa.NormalizarVector().Modulo();
		const float delta_x = largo - _largoEnReposo;

		Vector3D fuerza = PosicionRelativa * delta_x * _k;

		p->agregarFuerza(fuerza);
	}

	virtual void updateFuerzaRigidbody(physx::PxRigidDynamic* rigidbody, double t) override {
		PxVec3 posRel = rigidbody->getGlobalPose().p - _p->getPos().p;
		Vector3D PosicionRelativa = Vector3D(posRel.x, posRel.y, posRel.z);

		const float largo = PosicionRelativa.NormalizarVector().Modulo();
		const float delta_x = largo - _largoEnReposo;

		Vector3D fuerza = PosicionRelativa * delta_x * _k;

		rigidbody->addForce(PxVec3(fuerza.X(), fuerza.Y(), fuerza.Z()));
	}

	inline void setK(double k) { _k = k; }

	virtual ~GeneradorFuerzasMuelle(){}

	FUERZAS getTipo() { return _tipo; }
protected:
	double _k;
	double _largoEnReposo;
	Particula* _p;

	FUERZAS _tipo = FUERZAS::MUELLE_MOVIL;
};