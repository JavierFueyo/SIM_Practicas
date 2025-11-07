#include "SistemaParticulas.h"
#include <iostream>

using namespace physx;

//Emisor
Emisor::Emisor(Vector3D SpawnPos, Vector3D SpawnPosVar, int DistribType, Vector3D VelMin,
	Vector3D VelMax, Vector3D VelMedia, Vector3D VelDesviacion, Vector4 Color, ForceGenerator* GeneradorFuerzas, float SpawnRate,
	float LifeTime, float Radius, float Damping, float Mass, bool On) :
	_spawnPos(SpawnPos), _spawnPosVar(SpawnPosVar), _spawnRate(SpawnRate), _lifeTime(LifeTime), _radius(Radius), _distribType(DistribType),
	_velMin(VelMin), _velMax(VelMax), _velMedia(VelMedia), _velDesviacion(VelDesviacion), _damping(Damping), _mass(Mass), _color(Color), _on(On),
	_generadorFuerzas(GeneradorFuerzas)
{
	std::random_device rd;
	rng.seed(rd());
}

void 
Emisor::Spawn(double t) {
	_tiempoDesdeUltimoSpawn += t;
	if (_on && (_tiempoDesdeUltimoSpawn >= _spawnRate)) {
		std::uniform_real_distribution<float> varX(-_spawnPosVar.X(), _spawnPosVar.X());
		std::uniform_real_distribution<float> varY(-_spawnPosVar.Y(), _spawnPosVar.Y());
		std::uniform_real_distribution<float> varZ(-_spawnPosVar.Z(), _spawnPosVar.Z());
		Vector3D newPos = _spawnPos + Vector3D(varX(rng), varY(rng), varZ(rng));

		Vector3D newVel;
		if (_distribType == 0 /*Uniforme*/) {
			std::uniform_real_distribution<float> velX(_velMin.X(), _velMax.X());
			std::uniform_real_distribution<float> velY(_velMin.Y(), _velMax.Y());
			std::uniform_real_distribution<float> velZ(_velMin.Z(), _velMax.Z());
			newVel = Vector3D(velX(rng), velY(rng), velZ(rng));
		}
		else { //Gauss
			std::normal_distribution<float> velX(_velMedia.X(), _velDesviacion.X());
			std::normal_distribution<float> velY(_velMedia.Y(), _velDesviacion.Y());
			std::normal_distribution<float> velZ(_velMedia.Z(), _velDesviacion.Z());
			newVel = Vector3D(velX(rng), velY(rng), velZ(rng));
		}
		Particula* p = new Particula(newPos, newVel, Vector3D(0.0f, 0.0f, 0.0f), _color, _generadorFuerzas, _radius, _damping, _mass);
		_particulas.push_back(p);
		_sistemaPadre->regParticulaAFuerzaSistema(p);
		_tiempoDesdeUltimoSpawn = 0;
	}
}

void
Emisor::Integrate(double t) {
	for (Particula* p : _particulas) {
		//p->integrarEulerSemiImplicito(t);
		if (_on) {
			p->integrarFuerzas(t);
		}
		else {
			delete p;
		}
	}
	if (!_on) _particulas.clear();
}

//Sistema particulas
SistemaParticulas::~SistemaParticulas()
{
	for (auto& ip : _particulas) {
		delete ip.p;
	}
	_particulas.clear();
	_emisores.clear();
}

void
SistemaParticulas::AgregarEmisor(Emisor* e) {
	int id = _sigIdEmisor++;
	e->setID(id);
	e->setPadre(this);
	_emisores.push_back(e);
}

void
SistemaParticulas::update(double t) {
	for (auto e : _emisores) {
		e->Spawn(t);
		e->Integrate(t);
	}
	ControlParticulas();
}

void
SistemaParticulas::ControlParticulas() {

	for (auto* e : _emisores)
	{
		auto& particulas = e->getParticulas();

		for (auto it = particulas.begin(); it != particulas.end(); )
		{
			Particula* p = *it;

			regParticulaAFuerzaSistema(p);
			PxTransform pos = p->getPos();
			float dist2 = pos.p.x * pos.p.x + pos.p.y * pos.p.y + pos.p.z * pos.p.z;

			bool dead = (p->getTimeAlive() >= e->getLifeTime() ||
				pos.p.y < _maxDistanceY ||
				dist2 > _maxDistanceFondo * _maxDistanceFondo);

			if (dead)
			{
				delete p;
				it = particulas.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}

void
SistemaParticulas::AgregarFuerzaSistema(TipoFuerza* tF, bool activa) {
	_fuerzasSistema.push_back({ tF, activa });

	for (auto& ip : _particulas) {
		if (ip.p) {
			ip.p->agregarTipoFuerza(tF, activa);
		}
	}
}

void 
SistemaParticulas::QuitarFuerzaSistema(TipoFuerza* tF)
{
	_fuerzasSistema.erase(std::remove_if(_fuerzasSistema.begin(),
		_fuerzasSistema.end(),
		[tF](const FuerzaSistema& sf) {
			return sf.tF == tF;
		}),
		_fuerzasSistema.end());

	for (auto& pi : _particulas) {
		if (pi.p) {
			pi.p->quitarTipoFuerza(tF);
		}
	}
}

void 
SistemaParticulas::setFuerzaSistemaActiva(TipoFuerza* tF, bool activa) {
	for (auto& fs : _fuerzasSistema) {
		if (fs.tF == tF) {
			fs.activa = activa;
			break;
		}
	}

	for (auto& ip : _particulas) {
		if (ip.p && ip.p->getForceGenerator()) {
			ip.p->getForceGenerator()->setActiva(tF, activa);
		}
	}
}

void
SistemaParticulas::setEmisorActivo(int id, bool activa) {
	for (auto& e : _emisores) {
		if (e->getID() == id) {
			e->OnOff(activa);
			break;
		}
	}
}

void 
SistemaParticulas::updatePosicionEmisor(int id, const Vector3D& pos) {
	for (auto& e : _emisores) {
		if (e->getID() == id) {
			e->setSpawnPos(pos);
			break;
		}
	}
}

bool 
SistemaParticulas::EmisorActivo(int id) const {
	for (const auto& e : _emisores) {
		if (e->getID() == id) {
			return e->isOn();
		}
	}
	return false;
}

void
SistemaParticulas::regParticulaAFuerzaSistema(Particula* p) {
	for (const auto& fs : _fuerzasSistema) {
		p->agregarTipoFuerza(fs.tF, fs.activa);
	}
}