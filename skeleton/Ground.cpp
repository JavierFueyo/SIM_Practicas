#include "Ground.h"

Ground::Ground(PxPhysics* Physics, PxScene* Scene, float sizeX, float sizeZ) : gPhysics(Physics), gScene(Scene)
{
	ground = gPhysics->createRigidStatic(PxTransform({ 0,0,0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(sizeX, 1, sizeZ), gMaterial);
	ground->attachShape(*shape);
	gScene->addActor(*ground);

	renderItem = new RenderItem(shape, ground, Vector4(0.0, 0.5, 0.0, 1.0));
}