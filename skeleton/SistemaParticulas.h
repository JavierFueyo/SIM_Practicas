#pragma once
#include "Vector3D.h"
#include "Particula.h"

class SistemaParticulas
{
public:
	SistemaParticulas(Vector3D SpawnPos = {0, 0, 0}, bool On = false, float Gravity = 0.0f);

	void OnOff() { _on = !_on; }

private:

	Vector3D _spawnPos;
	bool _on;
	float _gravity;

	int _particleLifeTime;
	float _velMax;
	float _velMin;
	Vector3D _dirMax;
	Vector3D _dirMin;

};