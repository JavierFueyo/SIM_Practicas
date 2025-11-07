#pragma once
#include "Vector3D.h";
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
using namespace physx;
extern PxMaterial* gMaterial;

class Ground {
public:
	Ground(float size = 100.0f);
	~Ground() {
		DeregisterRenderItem(renderItem);
		delete renderItem;
	}
private:
	RenderItem* renderItem;
};