#include "Enemy.h"


Enemy::Enemy(PxPhysics* Physics, PxScene* Scene, ForceGenerator* Generador, PxRigidDynamic* morteroRB, float x, float y, float z,
	float sizeX, float sizeY, float sizeZ)
	: gPhysics(Physics), gScene(Scene), _generador(Generador), _morteroRB(morteroRB)
{
	_spawnPos = Vector3D(x,y,z);
	enemyRB = gPhysics->createRigidDynamic(PxTransform({ x,y,z }));
	PxMaterial* material = gPhysics->createMaterial(0.0f, 0.0f, 0.1f);
	PxShape* shape = CreateShape(PxBoxGeometry(sizeX/2, sizeY/2, sizeZ/2), material);
	enemyRB->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, true);
	enemyRB->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y, true);
	enemyRB->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, true);
	initialVel = enemyRB->getLinearVelocity();
	enemyRB->attachShape(*shape);
	PxRigidBodyExt::updateMassAndInertia(*enemyRB, 20.0f);

	gScene->addActor(*enemyRB);

	renderItem = new RenderItem(shape, enemyRB, Vector4(1, 1, 0, 1));
}

Enemy::~Enemy() {
	if (renderItem) {
		DeregisterRenderItem(renderItem);
		delete renderItem;
		renderItem = nullptr;
	}

	if (enemyRB && gScene) {
		gScene->removeActor(*enemyRB);
		enemyRB->release();
		enemyRB = nullptr;
	}
}

void
Enemy::agregarTipoFuerza(TipoFuerza* tF, bool activo) {
	_generador->addRB(enemyRB, tF, activo);
}

void
Enemy::setFuerzaActiva(TipoFuerza* tF, bool activo) {
	_generador->setActivaInd(enemyRB, tF, activo);
}

void
Enemy::update(double t) {

	PxVec3 dir = (_morteroRB->getGlobalPose().p - enemyRB->getGlobalPose().p);
	dir = dir.getNormalized();
	enemyRB->addForce(dir * 25000.0f);
	if (enemyRB->getGlobalPose().p.y <= -50.0f) timeFalling += t;
	if (timeFalling >= respawnTime) respawn();
}

void
Enemy::respawn() {
	enemyRB->setAngularVelocity({ 0,0,0 });
	enemyRB->setLinearVelocity({ 0,0,0 });
	enemyRB->clearForce();
	enemyRB->clearTorque();
	enemyRB->setGlobalPose(PxTransform(_spawnPos.X(), _spawnPos.Y(), _spawnPos.Z()));
	enemyRB->setLinearVelocity(initialVel);
	timeFalling = 0.0f;
}