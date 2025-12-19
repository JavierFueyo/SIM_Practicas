#pragma once
#include <PxPhysicsAPI.h>
#include "Vector3D.h"
class Particula;

enum FUERZAS { GRAVEDAD = 0, VIENTO = 1, TORBELLINO = 2, EXPLOSION = 3, MUELLE_MOVIL = 4, MUELLE_FIJO = 5, FLOTACION = 6 };

class TipoFuerza {
public:
	virtual ~TipoFuerza() = default;
	virtual void updateFuerza(Particula* p, double t) = 0;
	virtual void updateFuerzaRigidbody(physx::PxRigidDynamic* rigidbody, double t) = 0;
	virtual FUERZAS getTipo() = 0;
	virtual Vector3D getGrav() const { return Vector3D(); };
	virtual void setGrav(const Vector3D Gravity) {};

	FUERZAS _tipo;
};