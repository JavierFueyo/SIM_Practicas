#pragma once
#include "Particula.h"
#include "SistemaParticulas.h"
#include "ForceGenerator.h"
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"

class BalaCanion : public Proyectil {
public:
	BalaCanion(ForceGenerator* Generador, const Vector3D& Pos, const Vector3D& Vel, float Mass,
		float Damping, float Radius, float Gravity, const Vector4& Color)
		: Proyectil(Generador, Pos, Vel, Mass, Damping, Radius, Gravity, Color) {

	}
	~BalaCanion();
};