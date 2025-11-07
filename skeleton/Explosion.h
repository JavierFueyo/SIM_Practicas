#pragma once
#include "Particula.h"
#include "TipoFuerza.h"
#include <iostream>

class Explosion : public TipoFuerza {
public:
	Explosion(Vector3D PosicionCentro, float Radius, float K, float ConstTiempoExpl)
        : _posicionCentro(PosicionCentro), _radius(Radius), _K(K), _constTiempoExpl(ConstTiempoExpl)
    {}

	virtual void updateFuerza(Particula* p, double t) override {

        if (_activo) {
            if (p->getInverseMass() <= 0.0f)
                return;

            _tiempoPasado += t;

            if (_tiempoPasado >= 4.0f * _constTiempoExpl) {
                _activo = false;
                return;
            }

            Vector3D partPos = Vector3D(p->getPos().p.x, p->getPos().p.y, p->getPos().p.z);
            Vector3D distanciaVec = partPos - _posicionCentro;
            float distanciaMod = distanciaVec.Modulo();

            if (distanciaMod >= _radius || distanciaMod < 0.001f)
                return;

            float factorExpo = std::exp(-_tiempoPasado / _constTiempoExpl);
            float magnitudFuerza = (_K / (distanciaMod * distanciaMod)) * factorExpo;
            Vector3D fuerza = distanciaVec.NormalizarVector() * magnitudFuerza;
            p->agregarFuerza(fuerza);
        }
		
	}

    void BlowUp() { _activo = true; }

private:
    Vector3D _posicionCentro;
    float _radius, _K, _constTiempoExpl;
    bool _activo = false;
    float _tiempoPasado = 0;

	Vector3D _fuerzaExplosion;
};
