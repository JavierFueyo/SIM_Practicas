#pragma once
#include "Particula.h"
#include "SistemaParticulas.h"
#include "ForceGenerator.h"
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"

class BalaPiedra : public Proyectil {
public:
	BalaPiedra(ForceGenerator* Generador, const Vector3D& Pos, const Vector3D& Vel, float Mass,
		float Damping, float Radius, const Vector4& Color, bool Active)
		: Proyectil(Generador, BALAPIEDRA, Pos, Vel, Mass, Damping, Radius, Color, Active) {

	}
	~BalaPiedra() {};
};