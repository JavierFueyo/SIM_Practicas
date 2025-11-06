#pragma once
#include "Particula.h"
#include "TipoFuerza.h"

class Viento : public TipoFuerza {
public:
    Viento(const Vector3D& VelViento, float k1_ = 0.1f, float k2_ = 0.0f)
        : _velViento(VelViento), k1(k1_), k2(k2_) {}

    virtual void updateFuerza(Particula* p, double t) override
    {
        if (!p || p->getInverseMass() == 0)
            return;

        // Diferencia de velocidad (VelViento - VelParticula)
        Vector3D diferencia = _velViento - p->getVel();

        // Magnitud del flujo relativo
        float magnitud = diferencia.Modulo();

        // FuerzaViento = dif * k1 + dif * mag * k2
        Vector3D fuerza = diferencia * k1 +  diferencia * magnitud * k2;

        p->agregarFuerza(fuerza);
    }
    void setWindVelocity(const Vector3D& wVel) { _velViento = wVel; }


    const Vector3D& getWindVelocity() const { return _velViento; }

protected:
    Vector3D _velViento;  // Velocidad del viento
    float k1;              // Coeficiente de rozamiento lineal
    float k2;              // Coeficiente de rozamiento cuadrático (opcional)
};