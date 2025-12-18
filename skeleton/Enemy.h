//#pragma once
//#include "ForceGenerator.h"
//
//#include "RenderUtils.hpp"
//#include "Vector3D.h"
//extern PxMaterial* gMaterial;
//
//class Enemy {
//public:
//	Enemy(PxPhysics* Physics, PxScene* Scene, ForceGenerator* Generador, float x, float y, float z,
//		float sizeX = 100.0f, float sizeY = 100.0f, float sizeZ = 100.0f);
//
//	~Enemy();
//
//	void agregarTipoFuerza(TipoFuerza* tF, bool activo = true);
//	void setFuerzaActiva(TipoFuerza* tF, bool activo);
//	void clearFuerzas();
//
//	void update(double t);
//	void respawn();
//
//	PxRigidDynamic* getRB() { return enemyRB; };
//
//private:
//	PxPhysics* gPhysics = NULL;
//	PxScene* gScene = NULL;
//	PxRigidDynamic* enemyRB = NULL;
//	RenderItem* renderItem;
//
//	ForceGenerator* _generador;
//	float respawnTime = 5.0f;
//	float timeFalling = 0.0f;
//};