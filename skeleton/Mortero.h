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
	Mortero(float size, ForceGenerator* generador, Gravedad* G, Viento* V, Explosion* E, float w = 10.0f)
		: _w(w), _generador(generador), _g(G), _v(V), _e(E) {
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
		
		_sistemaHumo = new SistemaParticulas();

		Emisor* humoMortero = new Emisor(Vector3D(_trCuerpo.p.x, _trCuerpo.p.y + size, _trCuerpo.p.z),
			Vector3D(size / 1.5, size, size / 1.5), 1, Vector3D(0.2f, 0.2f, 0.2f), Vector3D(0.8f, 0.8f, 0.8f), Vector3D(0.0f, 0.0f, 0.0f),
			Vector3D(1.0f, 1.0f, 1.0f), Vector4(0.9, 0.9, 0.9, 1), generador, 0.1f, 1.0f, 5.0f, 0.99f, 0.01f, false);

		_sistemaHumo->AgregarEmisor(humoMortero);

		_sistemaExplosion = new SistemaParticulas();

		Emisor* dinaBum = new Emisor(Vector3D(_trCuerpo.p.x, _trCuerpo.p.y + size, _trCuerpo.p.z),
			Vector3D(0.2f, 0.2f, 0.2f), 1, Vector3D(0.2f, 0.2f, 0.2f), Vector3D(0.8f, 0.8f, 0.8f), Vector3D(0.0f, 0.0f, 0.0f),
			Vector3D(1.0f, 1.0f, 1.0f), Vector4(1, 0, 0, 1), generador, 0.1f, 2.0f, 5.0f, 0.99f, 1.0f, false);

		_sistemaExplosion->AgregarEmisor(dinaBum);

		_sistemaExplosion->AgregarFuerzaSistema(_e, false);
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

	void shoot(int i) {
		Vector3D pos = Vector3D(_trCuerpo.p.x, _trCuerpo.p.y, _trCuerpo.p.z);

		Proyectil* bala;
		switch (i) {
		case 0:
			bala = new BalaPiedra(_generador, pos, _direction * 50.0f,
				4.0f, 0.99f, 4.0f, Vector4(0.2, 0.2, 0.2, 1), true);
			_proyectiles.push_back(bala);
			bala->agregarTipoFuerza(_g, _gravedadOn);
			bala->agregarTipoFuerza(_v, _vientoOn);
			
			break;
		case 1:
			bala = new BalaDinamita(_generador, pos, _direction * 50.0f,
				2.0f, 0.99f, 2.5f, Vector4(1, 0, 0, 1), true);
			_proyectiles.push_back(bala);
			bala->agregarTipoFuerza(_g, _gravedadOn);
			bala->agregarTipoFuerza(_v, _vientoOn);

			break;
		}
		
		_sistemaHumo->setEmisorActivo(0, true);
		_smokeOn = true;
	}

	void update(double t) {
		for (auto& p : _proyectiles) {
			p->integrarFuerzas(t);

			if (!_bombOff && p->getType() == BALADINAMITA && p->getPos().p.y < 1.0f && p->getPos().p.y > -1.0f) {
				_sistemaExplosion->updatePosicionEmisor(0, Vector3D(p->getPos().p.x, p->getPos().p.y, p->getPos().p.z));
				_sistemaExplosion->setEmisorActivo(0, true);
				_e->updateCentro(Vector3D(p->getPos().p.x, p->getPos().p.y, p->getPos().p.z));
				_bombOff = true;
			}
		}
		_sistemaHumo->update(t);

		if (_bombOff) {
			_sistemaExplosion->update(t);
			_timeBomb += t;
			if (_timeBomb >= _timeBombMax) {
				_sistemaExplosion->setEmisorActivo(0, false);
				_e->BlowUp();
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

	void Boom(Proyectil* p) {

	}

	void setVientoOnOff() { _vientoOn = !_vientoOn; }
	void setGravedadOnOff() { _gravedadOn = !_gravedadOn; }
private:
	float _w;
	Vector3D _direction = Vector3D(1.0f, 1.0f, 0.0f);
	float _ang = PxPi;
	RenderItem* _cuerpo;
	RenderItem* _pieDer;
	RenderItem* _pieIzq;
	
	PxTransform _trCuerpo;
	PxTransform pieDer;
	PxTransform pieIzq;

	std::vector<Proyectil*> _proyectiles;
	SistemaParticulas* _sistemaHumo;
	SistemaParticulas* _sistemaExplosion;

	bool _smokeOn = false;
	float _smoketime = 0.0f;
	float _smokeTimeMax = 1.0f;

	bool _bombOff = false;
	float _timeBomb = 0.0f;
	float _timeBombMax = 1.5f;

	ForceGenerator* _generador;
	Gravedad* _g;
	Viento* _v;
	Explosion* _e;
	bool _gravedadOn = true;
	bool _vientoOn = true;
};
