#pragma once
#include "Vector3D.h";
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
using namespace physx;
extern PxMaterial* gMaterial;

class Ground {
public:
	Ground(PxPhysics* Physics, PxScene* Scene, float sizeX = 100.0f, float sizeZ = 100.0f);

	~Ground() {
		DeregisterRenderItem(renderItem);
		delete renderItem;
	}

private:
	PxPhysics* gPhysics = NULL;
	PxScene* gScene = NULL;
	PxRigidStatic* ground = NULL;
	RenderItem* renderItem;
};