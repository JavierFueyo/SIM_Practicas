#pragma once
#include "Vector3D.h";
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include "Particula.h"
#include "ForceGenerator.h"
#include <cmath>
#include <vector>
using namespace physx;
extern PxMaterial* gMaterial;

class Mortero {
public:
	Mortero(float size, ForceGenerator* _generador, Gravedad* G, Viento* V, Explosion* E, PxPhysics* Physics, PxScene* Scene, float w = 10.0f)
		: _w(w), _generador(_generador), _g(G), _v(V), _e(E), gPhysics(Physics), gScene(Scene) {

		_trCuerpo = PxTransform(-130, size * 2, 0);
		morteroRB = gPhysics->createRigidDynamic(_trCuerpo);
		PxShape* _cuerpoShape = CreateShape(PxBoxGeometry(size, size * 2, size));
		morteroRB->attachShape(*_cuerpoShape);
		PxRigidBodyExt::updateMassAndInertia(*morteroRB, 0.1);
		morteroRB->setLinearVelocity(PxVec3(0, 0, 0));
		morteroRB->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, true);
		morteroRB->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y, true);
		morteroRB->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, true);
		morteroRB->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_LINEAR_X, true);
		morteroRB->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_LINEAR_Y, true);
		morteroRB->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
		gScene->addActor(*morteroRB);
		_cuerpo = new RenderItem(_cuerpoShape, morteroRB, Vector4(0, 0, 0.2, 0.1f));


		pieDer = PxTransform(-130, size*1.5f, size * 3 / 2);
		pieDerRB = gPhysics->createRigidDynamic(pieDer);
		PxShape* _pieShape = CreateShape(PxBoxGeometry(size / 2, size * 1.5f, size / 2));
		pieDerRB->attachShape(*_pieShape);
		PxRigidBodyExt::updateMassAndInertia(*pieDerRB, 0.1);
		pieDerRB->setLinearVelocity(PxVec3(0, 0, 0));
		pieDerRB->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, true);
		pieDerRB->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y, true);
		pieDerRB->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, true);
		pieDerRB->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_LINEAR_X, true);
		pieDerRB->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_LINEAR_Y, true);
		pieDerRB->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
		gScene->addActor(*pieDerRB);
		_pieDer = new RenderItem(_pieShape, Vector4(0, 0, 0.2, 0.1f));


		pieIzq = PxTransform(-130, size*1.5f, -size * 3 / 2);
		pieIzqRB = gPhysics->createRigidDynamic(pieIzq);
		pieIzqRB->attachShape(*_pieShape);
		PxRigidBodyExt::updateMassAndInertia(*pieIzqRB, 0.1);
		pieIzqRB->setLinearVelocity(PxVec3(0, 0, 0));
		pieIzqRB->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_X, true);
		pieIzqRB->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y, true);
		pieIzqRB->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z, true);
		pieIzqRB->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_LINEAR_X, true);
		pieIzqRB->setRigidDynamicLockFlag(PxRigidDynamicLockFlag::eLOCK_LINEAR_Y, true);
		pieIzqRB->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
		gScene->addActor(*pieIzqRB);
		_pieIzq = new RenderItem(_pieShape, Vector4(0, 0, 0.2, 0.1f));

		_cuerpo->transform = &_trCuerpo;
		_pieDer->transform = &pieDer;
		_pieIzq->transform = &pieIzq;
		
		jointDer = PxFixedJointCreate(
			*gPhysics,
			morteroRB, PxTransform(PxVec3(0, -size / 2, size * 3 / 2)),
			pieDerRB, PxTransform(PxVec3(0, 0, 0))
		);
		jointIzq = PxFixedJointCreate(
			*gPhysics,
			morteroRB, PxTransform(PxVec3(0, -size / 2, -size * 3 / 2)),
			pieIzqRB, PxTransform(PxVec3(0, 0, 0))
		);

		_sistemaHumo = new SistemaParticulas();

		humoMortero = new Emisor(Vector3D(_trCuerpo.p.x, _trCuerpo.p.y + size, _trCuerpo.p.z),
			Vector3D(size / 1.5, size, size / 1.5), 1, Vector3D(0.2f, 0.2f, 0.2f), Vector3D(0.8f, 0.8f, 0.8f), Vector3D(0.0f, 0.0f, 0.0f),
			Vector3D(1.0f, 1.0f, 1.0f), Vector4(0.9, 0.9, 0.9, 1), _generador, 0.1f, 1.0f, 5.0f, 0.99f, 0.01f, false);

		_sistemaHumo->AgregarEmisor(humoMortero);

		_sistemaExplosion = new SistemaParticulas();

		dinaBum = new Emisor(Vector3D(_trCuerpo.p.x, _trCuerpo.p.y + size, _trCuerpo.p.z),
			Vector3D(0.2f, 0.2f, 0.2f), 1, Vector3D(0.2f, 0.2f, 0.2f), Vector3D(1.5f, 1.5f, 1.5f), Vector3D(0.0f, 0.0f, 0.0f),
			Vector3D(1.0f, 1.0f, 1.0f), Vector4(1, 0, 0, 1), _generador, 0.02f, 1.0f, 1.0f, 0.99f, 1.0f, false);

		_sistemaExplosion->AgregarEmisor(dinaBum);

		_sistemaExplosion->AgregarFuerzaSistema(_e, false);

		_proyectiles.push_back(new BalaPiedra(gPhysics, gScene, _generador, PxVec3(-5000,0,0),
			PxVec3(_direction.X(), _direction.Y(), _direction.Z()),
			0.99f, 4.0f, Vector4(0.2, 0.2, 0.2, 1), true));
		_proyectiles.push_back(new BalaDinamita(gPhysics, gScene, _generador, PxVec3(-5000, 0, 0),
			PxVec3(_direction.X(), _direction.Y(), _direction.Z()),
			0.99f, 2.5f, Vector4(1, 0, 0, 1), true));

	}
	~Mortero();

	void rotarUpDown(int Dir) {

		float _wRad = PxPi / 180.0f * _w;
		if (Dir == 1/*arriba*/) {

			if (_ang < PxPi) {
				PxQuat rot(_ang + _wRad, PxVec3(0,0,1));
				_trCuerpo = PxTransform(_trCuerpo.p, rot);
				_ang += _wRad;

				float x = cos(_ang - (PxPi / 2)) * 2.5f;
				float y = sin(_ang - (PxPi / 2)) * 2.5f;
				humoMortero->setSpawnPos(Vector3D(morteroRB->getGlobalPose().p.x+x, morteroRB->getGlobalPose().p.y + y, morteroRB->getGlobalPose().p.z));
				//std::cout << _ang << " " << _w << std::endl;
			}

		}
		else if (Dir == -1 /*Abajo*/) {
			if (_ang > PxPi/2) {
				PxQuat rot(_ang - _wRad, PxVec3(0, 0, 1));
				_trCuerpo = PxTransform(_trCuerpo.p, rot);
				_ang -= _wRad;

				float x = cos(_ang - (PxPi / 2)) * 2.5f;
				float y = sin(_ang - (PxPi / 2)) * 2.5f;
				humoMortero->setSpawnPos(Vector3D(morteroRB->getGlobalPose().p.x + x, morteroRB->getGlobalPose().p.y + y, morteroRB->getGlobalPose().p.z));

				//std::cout << _ang << " " << _w << std::endl;
			}
		}

		_direction = Vector3D(cos(_ang - (PxPi / 2)), sin(_ang - (PxPi / 2)), 0);
	}

	void moverLR(double t, int Dir, float limit) {

		if (Dir == -1 && morteroRB->getGlobalPose().p.z > -limit) {
			//std::cout << Dir << std::endl;
			morteroRB->addForce(PxVec3(0, 0, Dir * 3666.67), PxForceMode::eFORCE);
			/*pieIzqRB->addForce(PxVec3(0, 0, Dir * 500), PxForceMode::eFORCE);
			pieDerRB->addForce(PxVec3(0, 0, Dir * 500), PxForceMode::eFORCE);*/
			pieIzq = pieIzqRB->getGlobalPose();
			_trCuerpo = morteroRB->getGlobalPose();
			pieDer = pieDerRB->getGlobalPose();
			//std::cout << pieIzqRB->getLinearVelocity().z << " " << morteroRB->getLinearVelocity().z << " " << pieDerRB->getLinearVelocity().z << std::endl;
			//std::cout << pieIzq.p.z << " " << _trCuerpo.p.z << " " << pieDer.p.z << std::endl;
			//std::cout << _trCuerpo.p.x << " " << _trCuerpo.p.y << " " << _trCuerpo.p.z << std::endl;
		}
		else if (Dir == 1 && morteroRB->getGlobalPose().p.z < limit) {
			//std::cout << Dir << std::endl;
			morteroRB->addForce(PxVec3(0, 0, Dir * 3666.67), PxForceMode::eFORCE);
			/*pieIzqRB->addForce(PxVec3(0, 0, Dir * 500), PxForceMode::eFORCE);
			pieDerRB->addForce(PxVec3(0, 0, Dir * 500), PxForceMode::eFORCE);*/
			pieDer = pieDerRB->getGlobalPose();
			_trCuerpo = morteroRB->getGlobalPose();
			pieIzq = pieIzqRB->getGlobalPose();
			//std::cout << pieIzqRB->getLinearVelocity().z << " " << morteroRB->getLinearVelocity().z << " " << pieDerRB->getLinearVelocity().z << std::endl;
			//std::cout << pieIzq.p.z << " " << _trCuerpo.p.z << " " << pieDer.p.z << std::endl;
			//std::cout << _trCuerpo.p.x << " " << _trCuerpo.p.y << " " << _trCuerpo.p.z << std::endl;
		}
		else {
			//std::cout << Dir << std::endl;
			morteroRB->setLinearVelocity(PxVec3(0, 0, 0));
			morteroRB->clearForce();
			_trCuerpo = morteroRB->getGlobalPose();
			pieDer = pieDerRB->getGlobalPose();
			pieIzq = pieIzqRB->getGlobalPose();
			//std::cout << pieIzq.p.z << " " << _trCuerpo.p.z << " " << pieDer.p.z << std::endl;
		}
	}

	//void addProyectil(Proyectil* pr) { _proyectiles.push_back(pr); }

	void shoot() {
		Vector3D pos = Vector3D(_trCuerpo.p.x, _trCuerpo.p.y, _trCuerpo.p.z);

		//switch (gBalaElegida) {
		//case 0:
		//	/*bala = new BalaPiedra(_generador, pos, _direction * 100.0f,
		//		4.0f, 0.99f, 4.0f, Vector4(0.2, 0.2, 0.2, 1), true);
		//	_proyectiles.push_back(bala);
		//	bala->agregarTipoFuerza(_g, _gravedadOn);
		//	bala->agregarTipoFuerza(_v, _vientoOn);*/
		//	break;
		//case 1:
		//	/*bala = new BalaDinamita(_generador, pos, _direction * 100.0f,
		//		2.0f, 0.99f, 2.5f, Vector4(1, 0, 0, 1), true);
		//	_proyectiles.push_back(bala);
		//	bala->agregarTipoFuerza(_g, _gravedadOn);
		//	bala->agregarTipoFuerza(_v, _vientoOn);*/

		//	break;
		//}

		float x = cos(_ang - (PxPi / 2)) * 6.0f;
		float y = sin(_ang - (PxPi / 2)) * 6.0f;

		_proyectiles[gBalaElegida]->getRB()->clearForce();
		_proyectiles[gBalaElegida]->getRB()->setLinearVelocity({0,0,0});
		_proyectiles[gBalaElegida]->getRB()->clearTorque();
		_proyectiles[gBalaElegida]->getRB()->setAngularVelocity({ 0,0,0 });
		_proyectiles[gBalaElegida]->getRB()->setGlobalPose(PxTransform(morteroRB->getGlobalPose().p.x + x,
			morteroRB->getGlobalPose().p.y + y, morteroRB->getGlobalPose().p.z));
		_proyectiles[gBalaElegida]->shootBala(_direction.NormalizarVector());
		
		_sistemaHumo->setEmisorActivo(0, true);
		_smokeOn = true;
	}

	void update(double t, int Dir, float limit) {

		moverLR(t, Dir, limit);
		humoMortero->setSpawnPos(Vector3D(humoMortero->getSpawnPos().X(), humoMortero->getSpawnPos().Y(), morteroRB->getGlobalPose().p.z));


		//Actualiza proyectiles
		for (auto& bala : _proyectiles) {
			if (!_bombOff && _proyectiles[gBalaElegida]->getType() == BALADINAMITA &&
				_proyectiles[gBalaElegida]->getRB()->getGlobalPose().p.y < 1.0f &&
				_proyectiles[gBalaElegida]->getRB()->getGlobalPose().p.y > -1.0f) {
				_e->updateCentro(Vector3D(_proyectiles[gBalaElegida]->getRB()->getGlobalPose().p.x,
					_proyectiles[gBalaElegida]->getRB()->getGlobalPose().p.y,
					_proyectiles[gBalaElegida]->getRB()->getGlobalPose().p.z));

				_sistemaExplosion->updatePosicionEmisor(0, Vector3D((_proyectiles[gBalaElegida]->getRB()->getGlobalPose().p.x,
					_proyectiles[gBalaElegida]->getRB()->getGlobalPose().p.y,
					_proyectiles[gBalaElegida]->getRB()->getGlobalPose().p.z)));
				_sistemaExplosion->setEmisorActivo(0, true);
				_bombOff = true;
			}
		}
		_sistemaHumo->update(t);
		

		//Controla explosion
		_sistemaExplosion->update(t);
		if (_bombOff) {
			_timeBomb += t;
			_sistemaExplosion->setFuerzaSistemaActiva(_e, true);
			if(!_e->getActive())_e->BlowUp();
			if (_timeBomb >= _timeBombMax) {
				if (_e->getActive())_e->BlowUp();
				_sistemaExplosion->setEmisorActivo(0, false);
				_bombOff = false;
				_timeBomb = 0;
			}
		}

		//Controla el humo del disparo
		if (_smokeOn) {
			_smoketime += t;
			if (_smoketime >= _smokeTimeMax) {
				_sistemaHumo->setEmisorActivo(0, false);
				_smokeOn = false;
				_smoketime = 0;
			}
		}
	}

	void setVientoOnOff() { _vientoOn = !_vientoOn; }
	void setGravedadOnOff() { _gravedadOn = !_gravedadOn; }

	void setBalaElegida(int i){
		_proyectiles[gBalaElegida]->getRB()->setGlobalPose(PxTransform(-2000, 0, 0));
		_proyectiles[gBalaElegida]->getRB()->clearForce();
		_proyectiles[gBalaElegida]->getRB()->clearTorque();
		_proyectiles[gBalaElegida]->getRB()->putToSleep();

		gBalaElegida = i;
		_proyectiles[i]->getRB()->wakeUp();
	}

	PxRigidDynamic* getRB() { return morteroRB; }

	PxRigidDynamic* getBalasRB(int i) { return _proyectiles[i]->getRB(); }

	int getnumBalas() { return _proyectiles.size(); }
private:
	PxPhysics* gPhysics = NULL;
	PxScene* gScene = NULL;

	float _w;
	Vector3D _direction = Vector3D(0.0f, 1.0f, 0.0f);
	float _ang = PxPi;
	RenderItem* _cuerpo;
	RenderItem* _pieDer;
	RenderItem* _pieIzq;
	
	PxTransform _trCuerpo;
	PxTransform pieDer;
	PxTransform pieIzq;

	std::vector<Bala*> _proyectiles;
	SistemaParticulas* _sistemaHumo;
	Emisor* humoMortero;
	SistemaParticulas* _sistemaExplosion;
	Emisor* dinaBum;

	bool _smokeOn = false;
	float _smoketime = 0.0f;
	float _smokeTimeMax = 1.0f;

	bool _bombOff = false;
	float _timeBomb = 0.0f;
	float _timeBombMax = 1.5f;

	int gBalaElegida = 0;

	ForceGenerator* _generador;
	Gravedad* _g;
	Viento* _v;
	Explosion* _e;
	bool _gravedadOn = true;
	bool _vientoOn = false;

	PxRigidDynamic* morteroRB;
	PxRigidDynamic* pieDerRB;
	PxRigidDynamic* pieIzqRB;

	PxFixedJoint* jointDer;
	PxFixedJoint* jointIzq;
};
