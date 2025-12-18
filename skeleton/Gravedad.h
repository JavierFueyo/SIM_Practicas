#pragma once
#include "TipoFuerza.h"
#include "Particula.h"
#include <iostream>

class Gravedad : public TipoFuerza {
public:
    Gravedad(const Vector3D& Gravity) : _grav(Gravity) {}

    virtual void updateFuerza(Particula* p, double t) override
    {
        if (p->getInverseMass() <= 0.0f)
            return;

        float pMass = p->getMass();
        Vector3D fuerza = _grav * pMass;

        p->agregarFuerza(fuerza);
    }

    virtual void updateFuerzaRigidbody(physx::PxRigidDynamic* rigidbody, double t) override {

        float pMass = rigidbody->getMass();
        Vector3D fuerza = _grav * pMass;

        rigidbody->addForce(PxVec3(fuerza.X(), fuerza.Y(), fuerza.Z()));
    }

    Vector3D getGrav() const override { return _grav; }

    void setGrav(const Vector3D Gravity) override { _grav = Gravity; }

    FUERZAS getTipo() { return _tipo; }

    
private:
    Vector3D _grav;

    FUERZAS _tipo = FUERZAS::GRAVEDAD;
};