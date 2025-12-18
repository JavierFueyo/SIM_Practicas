//#include "Enemy.h"
//
//
//Enemy::Enemy(PxPhysics* Physics, PxScene* Scene, ForceGenerator* Generador, float x, float y, float z,
//	float sizeX = 100.0f, float sizeY = 100.0f, float sizeZ = 100.0f)
//	: gPhysics(Physics), gScene(Scene), _generador(Generador)
//{
//	enemyRB = gPhysics->createRigidDynamic(PxTransform({ x,y,z }));
//	PxShape* shape = CreateShape(PxBoxGeometry(sizeX, sizeY, sizeZ), gMaterial);
//	enemyRB->attachShape(*shape);
//	gScene->addActor(*enemyRB);
//
//	renderItem = new RenderItem(shape, enemyRB, Vector4(0.0, 0.5, 0.0, 1.0));
//}
//
//void
//Enemy::agregarTipoFuerza(TipoFuerza* tF, bool activo) {
//	_generador->addRB(enemyRB, tF, activo);
//	/*fuerzas.push_back(tF);
//	fuerzasAct.push_back(activo);*/
//}
//
//void
//Enemy::setFuerzaActiva(TipoFuerza* tF, bool activo) {
//	_generador->setActivaInd(enemyRB, tF, activo);
//	/*for (int i = 0; i < fuerzas.size(); ++i) {
//		if (fuerzas[i] == tF) {
//			fuerzasAct[i] = activo;
//			return;
//		}
//	}*/
//}
//
//void
//Enemy::clearFuerzas() {
//	/*fuerzas.clear();
//	fuerzasAct.clear();*/
//}
//
//void
//Enemy::update(double t) {
//	if (enemyRB->getGlobalPose().p.y <= -50.0f) timeFalling += t;
//	if (timeFalling >= respawnTime) respawn();
//}
//
//void
//Enemy::respawn() {
//
//}