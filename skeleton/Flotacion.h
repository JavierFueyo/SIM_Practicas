#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class Flotacion : public TipoFuerza {
public:
	//Altura = alto partícula; h0 = altura borde líquido; h = altura particula
	Flotacion(float Altura, float Volumen, float Densidad,
		float x0, float x1, float z0, float z1, float h0 = 0.0f) :
		_altura(Altura), _volumen(Volumen), _densidadLiquido(Densidad),
		_x0(x0), _x1(x1), _z0(z0), _z1(z1), _h0(h0) {}

	virtual void updateFuerza(Particula* P, double t) {
		if (P->getPos().p.x > _x0 && P->getPos().p.x < _x1 && P->getPos().p.z > _z0 && P->getPos().p.z < _z1) {
			float h = P->getPos().p.y;

			Vector3D f(0, 0, 0);
			float inmerso = 0.0;
			if (h - _h0 > _altura * 0.5f) {
				inmerso = 0.0;
			}
			else if (_h0 - h > _altura * 0.5f) {
				inmerso = 1.0;
			}
			else {
				inmerso = (_h0 - h) / _altura + 0.5f;
			}
			f.setY(_densidadLiquido * _volumen * inmerso * _gravedad);
			P->agregarFuerza(f);
		}
		
	}

	inline void setDens(float Densidad) { _densidadLiquido = Densidad; }

	virtual ~Flotacion() {}

	FUERZAS getTipo() { return _tipo; }
protected:
	float _altura;
	float _volumen;
	float _densidadLiquido;
	float _x0, _x1, _z0, _z1;
	float _gravedad = 9.8;
	float _h0;

	FUERZAS _tipo = FUERZAS::FLOTACION;
};