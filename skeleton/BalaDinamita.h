#pragma once
#include "Particula.h"
#include "SistemaParticulas.h"
#include "ForceGenerator.h"
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include "Bala.h"

//class BalaDinamita : public Proyectil {
//public:
//	BalaDinamita(ForceGenerator* Generador, const Vector3D& Pos, const Vector3D& Vel, float Mass,
//		float Damping, float Radius, const Vector4& Color, bool Active)
//		: Proyectil(Generador, BALADINAMITA, Pos, Vel, Mass, Damping, Radius, Color, Active) {
//
//	}
//	~BalaDinamita() {};
//};

class BalaDinamita : public Bala {
public:
	BalaDinamita(PxPhysics* Physx, PxScene* Scene, ForceGenerator* Generador, const PxVec3& Pos, const PxVec3& Vel,
		float Damping, float Radius, const Vector4& Color, bool Active, int tipo)
		: Bala(Physx, Scene, Generador, Pos, Vel, Damping, Radius, Color, Active, tipo) {}
};