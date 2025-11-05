#include "SistemaParticulas.h"
#include <iostream>

Emisor::Emisor(Vector3D SpawnPos, Vector3D SpawnPosVar, int DistribType, Vector3D VelMin,
	Vector3D VelMax, Vector3D VelMedia, Vector3D VelDesviacion, Vector4 Color, float SpawnRate,
	float LifeTime, float Radius, float Gravity, float Damping, bool On) :
	_spawnPos(SpawnPos), _spawnPosVar(SpawnPosVar), _spawnRate(SpawnRate), _lifeTime(LifeTime), _radius(Radius), _distribType(DistribType),
	_velMin(VelMin), _velMax(VelMax), _velMedia(VelMedia), _velDesviacion(VelDesviacion), _gravity(Vector3D(0.0f, Gravity, 0.0f)), _damping(Damping), _color(Color), _on(On)
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
		_particulas.push_back(new Particula(newPos, newVel, _gravity, _color, _radius, _damping));
		_tiempoDesdeUltimoSpawn = 0;
	}
}

void
Emisor::Integrate(double t) {
	for (Particula* p : _particulas) {
		p->integrarEulerSemiImplicito(t);
	}
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

	for (auto& e : _emisores) {
		std::vector<Particula*> ParticulasEmisor = e->getParticulas();

		for (auto& p : ParticulasEmisor) {
			InstanciaParticula ip;
			ip.p = p;
			ip.tiempoDeVida = e->getLifeTime();
			_particulas.push_back(ip);
		}
	}
	std::vector<InstanciaParticula> ParticulasVivas;
	ParticulasVivas.reserve(_particulas.size());

	for (auto& ip : _particulas) {

		if (!ip.p) continue;

		PxTransform pos = ip.p->getPos();
		float dist2 = pos.p.x * pos.p.x + pos.p.y * pos.p.y + pos.p.z * pos.p.z;


		bool dead = (ip.tiempoDeVida <= ip.p->getTimeAlive() ||
			pos.p.y < _maxDistanceY ||
			dist2 > _maxDistanceFondo * _maxDistanceFondo);

		if (dead)
		{
			delete ip.p; //Fallo aqui
			ip.p = nullptr;
		}
		else
		{
			ParticulasVivas.push_back(ip);
		}
	}
	_particulas.swap(ParticulasVivas);




	/*for (auto e : _emisores) {
		std::vector<Particula*>& data = e->getParticulas();
		if (!data.empty()) {

			for (auto it = data.begin(); it != data.end();) {
				Particula* p = *it;
				float dist = p->getPos().p.x * p->getPos().p.x + p->getPos().p.y * p->getPos().p.y + p->getPos().p.z * p->getPos().p.z;
				
				if ((p->getTimeAlive() >= e->getLifeTime()) || dist >= _maxDistance) {
					delete p;
					it = data.erase(it);
				}
				else it++;
			}


			/*for (auto p : e->getParticulas()) {
				float dist = p->getPos().p.x * p->getPos().p.x + p->getPos().p.y * p->getPos().p.y + p->getPos().p.z * p->getPos().p.z;
				if ((p->getTimeAlive() >= e->getLifeTime()) || dist >= _maxDistance) {
					auto itAux = it;
					delete p;
					e->getParticulas().erase(itAux);
					it++;
				}
				else it++;
			}
		}
	}*/
}