#pragma once
#include "TipoFuerza.h"
#include "Particula.h"

class Gravedad : public TipoFuerza {
private:
    Vector3D _grav;

public:

    Gravedad(const Vector3D& Gravity) : _grav(Gravity) {}

    virtual void updateFuerza(Particula* p, double dt) override
    {
        if (p->getInverseMass() <= 0.0f)
            return;

        float pMass = p->getMass();
        Vector3D fuerza = _grav * pMass;

        p->agregarFuerza(fuerza);
    }

    Vector3D getGrav() const { return _grav; }

    void setGrav(const Vector3D Gravity) { _grav = Gravity; }
};