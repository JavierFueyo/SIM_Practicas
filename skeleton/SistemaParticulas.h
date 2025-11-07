#pragma once
#include <vector>
#include <random>
#include "Vector3D.h"
#include "Particula.h"
#include "ForceGenerator.h"

class SistemaParticulas;
class Emisor
{
public:
	Emisor(Vector3D SpawnPos, Vector3D SpawnPosVar, int DistribType, Vector3D VelMin, Vector3D VelMax, Vector3D VelMedia,
		Vector3D VelDesviacion, Vector4 Color,
		ForceGenerator* GeneradorFuerzas, float SpawnRate = 1.0f, float LifeTime = 1.0f, float Radius = 1.0f,
		float Damping = 1.0f, float Mass = 1.0f, bool On = true);

	~Emisor() {
		for (Particula* p : _particulas) {
			delete p;
		}
		_particulas.clear();
	}

	void OnOff(bool activa) { _on = activa; }

	void Spawn(double t);

	void Integrate(double t);

	std::vector<Particula*>& getParticulas() { return _particulas; }

	float getLifeTime() { return _lifeTime; }

	void setSpawnPos(Vector3D Pos) { _spawnPos = Pos; }

	void setID(int i) { _id = i; }
	int getID() { return _id; }

	bool isOn() { return _on; }

	void setPadre(SistemaParticulas* sp) { _sistemaPadre = sp; }
private:

	bool _on;
	std::vector<Particula*> _particulas;
	Vector3D _spawnPos, _spawnPosVar;
	float _spawnRate, _tiempoDesdeUltimoSpawn = 0, _lifeTime;
	int _distribType; // 0 = uniforme, 1 = Gauss
	Vector3D _velMin, _velMax;
	Vector3D _velMedia, _velDesviacion; //Para Gauss
	Vector3D _gravity;
	float _radius, _damping, _mass;
	Vector4 _color;

	std::mt19937 rng;

	SistemaParticulas* _sistemaPadre;
	ForceGenerator* _generadorFuerzas;

	int _id;
};

class SistemaParticulas
{
public:
	SistemaParticulas() {};

	~SistemaParticulas();


	void update(double t);

	void ControlParticulas();

	void AgregarFuerzaSistema(TipoFuerza* tF, bool activa = true);
	void QuitarFuerzaSistema(TipoFuerza* tF);
	void setFuerzaSistemaActiva(TipoFuerza* tF, bool activa);


	void AgregarEmisor(Emisor* e);
	void setEmisorActivo(int id, bool activa);
	void updatePosicionEmisor(int id, const Vector3D& pos);
	bool EmisorActivo(int id) const;
	void VaciarEmisores() { _emisores.clear(); _sigIdEmisor = 0; }
	std::vector<Emisor*>& getEmisores() { return _emisores; }

	void regParticulaAFuerzaSistema(Particula* p);
private:
	struct InstanciaParticula {
		Particula* p;
		float tiempoDeVida;
	};
	struct FuerzaSistema {
		TipoFuerza* tF;
		bool activa;
	};

	std::vector<Emisor*> _emisores;
	int _sigIdEmisor = 0;
	std::vector<InstanciaParticula> _particulas;
	float _maxDistanceY = -50.0f;
	float _maxDistanceFondo = 500.0f;

	std::vector<FuerzaSistema> _fuerzasSistema;
	ForceGenerator* _generadorFuerzas;
};