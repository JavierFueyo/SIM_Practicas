#pragma once
#include "Vector3D.h"
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
using namespace physx;
extern PxMaterial* gMaterial;

class Ground {
public:
	Ground(PxPhysics* Physics, PxScene* Scene, float x, float y, float z, float sizeX = 100.0f, float sizeZ = 100.0f);

	~Ground() {
		DeregisterRenderItem(renderItem);
		delete renderItem;
	}

	PxRigidStatic* getRB() { return ground; };

private:
	PxPhysics* gPhysics = NULL;
	PxScene* gScene = NULL;
	PxRigidStatic* ground = NULL;
	RenderItem* renderItem;
};