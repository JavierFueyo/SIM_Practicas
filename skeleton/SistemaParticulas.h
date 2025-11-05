#pragma once
#include <vector>
#include <random>
#include "Vector3D.h"
#include "Particula.h"

class Emisor
{
public:
	Emisor(Vector3D SpawnPos, Vector3D SpawnPosVar, int DistribType, Vector3D VelMin, Vector3D VelMax, Vector3D VelMedia,
		Vector3D VelDesviacion, Vector4 Color, float SpawnRate = 1.0f, float LifeTime = 1.0f, float Radius = 1.0f, 
		float Gravity = -9.8f, float Damping = 1.0f, bool On = true);

	~Emisor() {
		for (Particula* p : _particulas) {
			delete p;
		}
		_particulas.clear();
	}

	void OnOff() { _on = !_on; }

	void Spawn(double t);

	void Integrate(double t);

	std::vector<Particula*>& getParticulas() { return _particulas; }

	float getLifeTime() { return _lifeTime; }
private:

	bool _on;
	std::vector<Particula*> _particulas;
	Vector3D _spawnPos, _spawnPosVar;
	float _spawnRate, _tiempoDesdeUltimoSpawn = 0, _lifeTime;
	int _distribType; // 0 = uniforme, 1 = Gauss
	Vector3D _velMin, _velMax;
	Vector3D _velMedia, _velDesviacion; //Para Gauss
	Vector3D _gravity;
	float _radius, _damping;
	Vector4 _color;

	std::mt19937 rng;
};

class SistemaParticulas
{
public:
	SistemaParticulas() {};
	~SistemaParticulas();

	void AñadirEmisor(Emisor* e) { _emisores.push_back(e); }

	void update(double t);

	void ControlParticulas();


private:
	struct InstanciaParticula {
		Particula* p;
		float tiempoDeVida;
	};

	std::vector<Emisor*> _emisores;
	std::vector<InstanciaParticula> _particulas;
	float _maxDistanceY = -50.0f;
	float _maxDistanceFondo = 500.0f;
};