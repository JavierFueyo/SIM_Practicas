#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>
#include <vector>

#include "Vector3D.h"
#include "Particula.h"
#include "SistemaParticulas.h"
#include "ForceGenerator.h"
#include "Gravedad.h"
#include "Viento.h"
#include "Torbellino.h"
#include "Explosion.h"

std::string display_text = "This Is A Test";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

//Practica1
Particula* p;
Particula* q;
Particula* r;
//std::vector<Particula*> _partVect;
Proyectil* proy;

//Practica 2
SistemaParticulas* s = new SistemaParticulas();

//Practica3
ForceGenerator* _generador = new ForceGenerator();
Gravedad* _gravedad1 = new Gravedad(Vector3D(0.0f, -9.8f, 0.0f));
Gravedad* _gravedad2 = new Gravedad(Vector3D(0.0f, -5.0f, 0.0f));
Viento* _viento = new Viento(Vector3D(10.0f,0.0f,0.0f));
Torbellino* _torbellino = new Torbellino(Vector3D(0.0f,0.0f,0.0f), 40.0f, 5.0f, 0.1f, 0.0f);
Explosion* _explosion = new Explosion(Vector3D(0.0f, 0.0f, 0.0f), 50.0f, 10.0f, 1.0f);

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	//Ejes de coordenadas
	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
	PxSphereGeometry sphere(1.0f);
	//RenderItem* cSphere = new RenderItem(CreateShape(sphere, gMaterial), {1,1,1,1});
	PxTransform* xTransform = new PxTransform({ 10.0f, 0.0f, 0.0f });
	PxTransform* yTransform = new PxTransform({ 0.0f, 10.0f, 0.0f });
	PxTransform* zTransform = new PxTransform({ 0.0f, 0.0f, 10.0f });
	//RenderItem* xSphere = new RenderItem(CreateShape(sphere, gMaterial), xTransform, { 1, 0, 0, 1 });
	//RenderItem* ySphere = new RenderItem(CreateShape(sphere, gMaterial), yTransform, { 0, 1, 0, 1 });
	//RenderItem* zSphere = new RenderItem(CreateShape(sphere, gMaterial), zTransform, { 0, 0, 1, 1 });


	//Practica 1: particula
	/*p = new Particula(Vector3D(0.0f, 0.0f, 0.0f), Vector3D(10.0f, 0.0f, 0.0f), Vector3D(1.0f, 0.0f, 0.0f), 1.0f, 1.0f, 1.0f);
	*/

	//Practica 2: Sistema de particulas
	/*Emisor* e1 = new Emisor(Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.5f, 0.5f, 0.5f), 1,
		Vector3D(1.0f, 1.0f, 1.0f), Vector3D(3.0f, 3.0f, 3.0f), Vector3D(0.0f, 0.0f, 0.0f),
		Vector3D(1.0f, 1.0f, 1.0f), Vector4(1, 0, 0, 1), 1.0f, 2.0f, 0.5f, -9.8, 0.99, true);

	Emisor* e2 = new Emisor(Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.4f, 0.4f, 0.4f), 1,
		Vector3D(1.0f, 1.0f, 1.0f), Vector3D(3.0f, 3.0f, 3.0f), Vector3D(0.0f, 0.0f, 0.0f),
		Vector3D(1.0f, 1.0f, 1.0f), Vector4(1, 0.5, 0, 1), 0.2f, 2.0f, 0.4f, -9.8, 0.99, true);

	Emisor* e3 = new Emisor(Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.3f, 0.3f, 0.3f), 1,
		Vector3D(1.0f, 1.0f, 1.0f), Vector3D(3.0f, 3.0f, 3.0f), Vector3D(0.0f, 0.0f, 0.0f),
		Vector3D(1.0f, 1.0f, 1.0f), Vector4(1, 1, 0, 1), 0.2f, 2.0f, 0.3f, -9.8, 0.99, true);

	s->AñadirEmisor(e1);
	s->AñadirEmisor(e2);
	s->AñadirEmisor(e3);*/

	//Practica 3: Generadores de fuerzas
	//p = new Particula(Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), Vector4(1, 1, 1, 1), 1.0f, 0.99f, 1.0f);
	//q = new Particula(Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 1.0f), Vector4(1, 1, 1, 1), 1.0f, 0.99f, 1.0f);
	//r = new Particula(Vector3D(1.0f, 0.0f, 1.0f), Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), Vector4(1, 1, 1, 1), _generador, 1.0f, 0.99f, 1.0f);
	//generador.add(p, _gravedad1, true);
	//generador.add(p, _viento, true);
	//generador.add(q, _gravedad1, true);
	//generador.add(q, _torbellino, true);
	
	/*Emisor* e = new Emisor(Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.5f, 0.5f, 0.5f), 1,
		Vector3D(1.0f, 1.0f, 1.0f), Vector3D(3.0f, 3.0f, 3.0f), Vector3D(0.0f, 0.0f, 0.0f),
		Vector3D(1.0f, 1.0f, 1.0f), Vector4(1, 0, 0, 1), _generador, 0.1f, 2.0f, 0.5f, 0.99f, 1.0f, true);
	s->AgregarEmisor(e);
	s->AgregarFuerzaSistema(_gravedad1, true);*/

	proy = new Proyectil(_generador, Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 2.0f, 0.99f, 10.0f, -9.8f, Vector4(0.5f, 0.5f, 0.5f, 1.0f));
	_generador->add(proy, _viento, true);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	//p->integrarEulerSemiImplicito(t);
	//p->integrarVerlet(t);
	
	//s->update(t);
	
	//_generador->updateFuerzas(t);
	//_gravedad1->updateFuerza(p, t);
	//_gravedad1->updateFuerza(q, t);
	//_viento->updateFuerza(p, t);
	//_torbellino->updateFuerza(q, t);
	//_explosion->updateFuerza(r, t);
	//p->integrarFuerzas(t);
	//q->integrarFuerzas(t);
	//r->integrarFuerzas(t);
	proy->integrarFuerzas(t);


	//for (Particula* q : _partVect) {
	//	if (q) q->integrarEulerSemiImplicito(t);
	//}
	

	gScene->simulate(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
	}

void shootProjectile() {
	/*Camera* _cam = GetCamera();
	PxVec3 pos = _cam->getEye();
	PxVec3 dir = _cam->getDir();
	Vector3D _pos = Vector3D(pos.x, pos.y, pos.z);
	Vector3D _dir = Vector3D(dir.x, dir.y, dir.z);
	std::cout << "A";
	if (!_partVect.empty()) {
		delete _partVect.back();
	}
	_partVect.push_back(new Particula(_pos, _dir * 50.0f, Vector3D(0.0f, 0.0f, 0.0f), Vector4(1,1,1,1), 1.0f, 1.0f, 1.0f));*/

	proy->setActivo(true);
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case ' ':
	{
		break;
	}
	case 'P':
		shootProjectile();
		break;
	case 'E':
		std::cout << "E" << std::endl;
		_explosion->BlowUp();
		break;
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}



int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}