#pragma once
#include "Particula.h"
#include "SistemaParticulas.h"
#include "ForceGenerator.h"
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include "Bala.h"

//class BalaPiedra : public Proyectil {
//public:
//	BalaPiedra(ForceGenerator* Generador, const Vector3D& Pos, const Vector3D& Vel, float Mass,
//		float Damping, float Radius, const Vector4& Color, bool Active)
//		: Proyectil(Generador, BALAPIEDRA, Pos, Vel, Mass, Damping, Radius, Color, Active) {
//
//	}
//	~BalaPiedra() {};
//};

class BalaPiedra : public Bala {
public:
	BalaPiedra(PxPhysics* Physx, PxScene* Scene, ForceGenerator* Generador, const PxVec3& Pos, const PxVec3& Vel,
		float Damping, float Radius, const Vector4& Color, bool Active)
		: Bala(Physx, Scene, Generador, Pos, Vel, Damping,Radius,Color,Active) {}
};