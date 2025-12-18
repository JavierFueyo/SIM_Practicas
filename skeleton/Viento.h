#pragma once
#include "Particula.h"
#include "TipoFuerza.h"

class Viento : public TipoFuerza {
public:
    Viento(const Vector3D& VelViento, float k1_ = 0.1f, float k2_ = 0.0f)
        : _velViento(VelViento), _k1(k1_), _k2(k2_) {}

    virtual void updateFuerza(Particula* p, double t) override
    {
        if (!p || p->getInverseMass() == 0)
            return;

        // Diferencia de velocidad (VelViento - VelParticula)
        Vector3D diferencia = _velViento - p->getVel();

        // Magnitud del flujo relativo
        float magnitud = diferencia.Modulo();

        // FuerzaViento = dif * k1 + dif * mag * k2
        Vector3D fuerza = diferencia * _k1 +  diferencia * magnitud * _k2;

        p->agregarFuerza(fuerza);
    }

    virtual void updateFuerzaRigidbody(physx::PxRigidDynamic* rigidbody, double t) override {
        // Diferencia de velocidad (VelViento - VelParticula)
        Vector3D diferencia = _velViento - Vector3D(rigidbody->getLinearVelocity().x, rigidbody->getLinearVelocity().y, rigidbody->getLinearVelocity().z);

        // Magnitud del flujo relativo
        float magnitud = diferencia.Modulo();

        // FuerzaViento = dif * k1 + dif * mag * k2
        Vector3D fuerza = diferencia * _k1 + diferencia * magnitud * _k2;

        rigidbody->addForce(PxVec3(fuerza.X(), fuerza.Y(), fuerza.Z()));
    }

    void setWindVelocity(const Vector3D& wVel) { _velViento = wVel; }

    const Vector3D& getWindVelocity() const { return _velViento; }

    FUERZAS getTipo() { return _tipo; }
protected:
    Vector3D _velViento;  // Velocidad del viento
    float _k1;              // Coeficiente de rozamiento lineal
    float _k2;              // Coeficiente de rozamiento cuadrático (opcional)

    FUERZAS _tipo = FUERZAS::GRAVEDAD;
};