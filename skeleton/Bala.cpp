#include "Bala.h"

Bala::Bala(PxPhysics* physx, PxScene* Scene, ForceGenerator* Generador, const PxVec3& Pos, const PxVec3& Vel,
	float Damping, float Radius, const Vector4& Color, bool Active, int tipo)
	: gPhysx(physx), gScene(Scene), _generador(Generador), type(tipo)
{

	rb = gPhysx->createRigidDynamic(PxTransform(Pos));
	PxShape* shape = CreateShape(PxSphereGeometry((PxReal)Radius), gMaterial);
	rb->attachShape(*shape);
	rb->setLinearDamping(Damping);
	PxRigidBodyExt::updateMassAndInertia(*rb, 2200.0);

	gScene->addActor(*rb);
	renderItem = new RenderItem(shape, rb, Color);

}

Bala::~Bala() {
	if (renderItem) {
		DeregisterRenderItem(renderItem);
		delete renderItem;
	}
	if (rb && gScene) {
		gScene->removeActor(*rb);
		rb->release();
	}
}
void
Bala::agregarTipoFuerza(TipoFuerza* tF, bool activo) {
	_generador->addRB(rb, tF, activo);
	fuerzas.push_back(tF);
	fuerzasAct.push_back(activo);
}

void
Bala::setFuerzaActiva(TipoFuerza* tF, bool activo) {
	_generador->setActivaInd(rb, tF,activo);
	for (int i = 0; i < fuerzas.size(); ++i) {
		if (fuerzas[i] == tF) {
			fuerzasAct[i] = activo;
			return;
		}
	}
}

void
Bala::clearFuerzas() {
	fuerzas.clear();
	fuerzasAct.clear();
}

void
Bala::shootBala(Vector3D direction) {
	PxVec3 dir(direction.X(), direction.Y(), direction.Z());
	rb->setLinearVelocity(dir * 50.0f);
}