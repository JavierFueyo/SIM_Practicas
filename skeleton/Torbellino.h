#pragma once
#include "Particula.h"
#include "TipoFuerza.h"
#include "Viento.h"

class Torbellino : public Viento {
public:
    Torbellino(const Vector3D& PosCentral, float Radius, float K, float k1, float k2)
        : _posCentral(PosCentral), _radius(Radius), _K(K), Viento(Vector3D(0.0f, 0.0f, 0.0f), k1, k2)
    {}

    virtual void updateFuerza(Particula* p, double t) override {
        if (!p || p->getInverseMass() == 0) return;

        Vector3D partPos = Vector3D(p->getPos().p.x, p->getPos().p.y, p->getPos().p.z);

        float _velVientoZ = -(partPos.Z() - _posCentral.Z());
        float _velVientoY = 50 - (partPos.Y() - _posCentral.Y());
        float _velVientoX = partPos.X() - _posCentral.X();

        Vector3D _viento = Vector3D(_velVientoX, _velVientoY, _velVientoZ) * _K;
        float distancia = (partPos - _posCentral).Modulo();
        if (distancia > _radius) return;

        setWindVelocity(_viento);
        Viento::updateFuerza(p, t);
    }

    FUERZAS getTipo() { return _tipo; }
private:
    Vector3D _posCentral;
    float _radius, _K;

    FUERZAS _tipo = FUERZAS::GRAVEDAD;
};
