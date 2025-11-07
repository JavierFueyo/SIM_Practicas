#pragma once
#include "Vector3D.h";
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
using namespace physx;
extern PxMaterial* gMaterial;

class Ground {
public:
	Ground(float size) {
		PxBoxGeometry floor(size, 1, size);
		renderItem = new RenderItem(CreateShape(floor, gMaterial), &PxTransform({0,0,0}), Vector4(0, 1, 0, 1));
	}
private:
	RenderItem* renderItem;
};