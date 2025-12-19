#include "Ground.h"

Ground::Ground(PxPhysics* Physics, PxScene* Scene, float x, float y, float z, float sizeX, float sizeZ) : gPhysics(Physics), gScene(Scene)
{
	ground = gPhysics->createRigidStatic(PxTransform({ x,y,z }));
	PxMaterial* material = gPhysics->createMaterial(0.0f, 0.0f, 0.1f);
	PxShape* shape = CreateShape(PxBoxGeometry(sizeX, 1, sizeZ), material);
	ground->attachShape(*shape);
	gScene->addActor(*ground);

	renderItem = new RenderItem(shape, ground, Vector4(0.0, 0.5, 0.0, 1.0));
}