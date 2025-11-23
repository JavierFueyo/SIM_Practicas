#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class Flotacion : public TipoFuerza {
public:
	Flotacion(float Altura, float Volumen, float Densidad) :
		_altura(Altura), _volumen(Volumen), _densidadLiquido(Densidad);

	virtual void updateFuerza(Particula* P) {
		float h = P->getPos().p.y;
		float h0 = _pLiquido->getPos().p.y;

		Vector3D f(0, 0, 0);
		float inmerso = 0.0;
		if (h - h0 > _altura * 0.5) {
			inmerso = 0.0;
		}
		else if (h0 - h > _altura * 0.5) {
			inmerso = 1.0;
		}
		else {
			inmerso = (h0 - h) / _altura + 0.5;
		}
		f.setY(_densidadLiquido * _volumen * inmerso * _gravedad);
		P->agregarFuerza(f);
	}

	virtual ~Flotacion(); 

protected:
	float _altura;
	float _volumen;
	float _densidadLiquido;
	float _gravedad = 9.8;

	Particula* _pLiquido;
};