#pragma once
#include "Vector3D.h";
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include "Particula.h"
#include "ForceGenerator.h"
#include <vector>
using namespace physx;
extern PxMaterial* gMaterial;

class Mortero {
public:
	Mortero(float size, ForceGenerator* generador, float w = 10.0f) : _w(w), _generador(generador) {
		PxBoxGeometry cuerpo(size, size * 2, size);
		PxBoxGeometry pie(size / 2, size*1.5f, size / 2);
		_cuerpo = new RenderItem(CreateShape(cuerpo, gMaterial), Vector4(0, 0, 0.2, 1));
		_pieDer = new RenderItem(CreateShape(pie, gMaterial), Vector4(0, 0, 0.2, 1));
		_pieIzq = new RenderItem(CreateShape(pie, gMaterial), Vector4(0, 0, 0.2, 1));

		_trCuerpo = PxTransform(-90, size*2, 0);
		_cuerpo->transform = &_trCuerpo;

		pieDer = PxTransform(-90, size*1.5f, size * 3 / 2);
		_pieDer->transform = &pieDer;

		pieIzq = PxTransform(-90, size*1.5f, -size * 3 / 2);
		_pieIzq->transform = &pieIzq;
		
	}
	~Mortero();

	void rotarUpDown(bool Dir) {
		float _wRad = PxPi / 180.0f * _w;
		if (Dir /*arriba*/) {

			if (_ang < PxPi) {
				PxQuat rot(_ang + _wRad, PxVec3(0,0,1));
				_trCuerpo = PxTransform(_trCuerpo.p, rot);
				_ang += _wRad;
				std::cout << _ang << " " << _w << std::endl;
			}

		}
		else {
			if (_ang > PxPi/2) {
				PxQuat rot(_ang - _wRad, PxVec3(0, 0, 1));
				_trCuerpo = PxTransform(_trCuerpo.p, rot);
				_ang -= _wRad;
				std::cout << _ang << " " << _w << std::endl;
			}
		}
	}

	void addProyectil(Proyectil* pr) { _proyectiles.push_back(pr); }

	void shoot() {
		Vector3D pos = Vector3D(_trCuerpo.p.x, _trCuerpo.p.y, _trCuerpo.p.z);
		std::cout << "A";

		_proyectiles.push_back(new BalaPiedra(_generador, pos, _direction * 100.0f, 1.0, 0.99f, 3.0f, Vector4(0.2, 0.2, 0.2, 1), true));
	}

	void update(double t) {
		for (auto& p : _proyectiles) {
			p->integrarFuerzas(t);
		}
	}

private:
	float _w;
	Vector3D _direction = Vector3D(0.0f, 1.0f, 0.0f);
	float _ang = PxPi;
	RenderItem* _cuerpo;
	RenderItem* _pieDer;
	RenderItem* _pieIzq;
	
	PxTransform _trCuerpo;
	PxTransform pieDer;
	PxTransform pieIzq;

	std::vector<Proyectil*> _proyectiles;
	ForceGenerator* _generador;
};
