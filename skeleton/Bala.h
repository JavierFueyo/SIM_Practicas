#pragma once
#include "Particula.h"
#include "SistemaParticulas.h"
#include "ForceGenerator.h"
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
extern PxMaterial* gMaterial;

class Bala {
public:
	Bala(PxPhysics* physx, PxScene* Scene, ForceGenerator* Generador, const PxVec3& Pos, const PxVec3& Vel,
		float Damping, float Radius, const Vector4& Color, bool Active);

	~Bala();
	void agregarTipoFuerza(TipoFuerza* tF, bool activo = true);
	void setFuerzaActiva(TipoFuerza* tF, bool activo);
	void clearFuerzas();
	//void integrarFuerzas(double dt);

	void shootBala(Vector3D direccion);

	PxRigidDynamic* getRB() { return rb; };
	int getType() { return type; }

private:
	PxRigidDynamic* rb;
	PxScene* gScene;
	PxPhysics* gPhysx;
	RenderItem* renderItem;

	ForceGenerator* _generador;
	std::vector<TipoFuerza*> fuerzas;
	std::vector<bool> fuerzasAct;

	int type;
};