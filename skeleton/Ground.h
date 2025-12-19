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
        if (renderItem) {
            DeregisterRenderItem(renderItem);
            delete renderItem;
            renderItem = nullptr;
        }
        if (ground && gScene) {
            gScene->removeActor(*ground);
            ground->release();
            ground = nullptr;
        }
	}

	PxRigidStatic* getRB() { return ground; };

private:
	PxPhysics* gPhysics = NULL;
	PxScene* gScene = NULL;
	PxRigidStatic* ground = NULL;
	RenderItem* renderItem;
};