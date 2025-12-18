#pragma once
#include "TipoFuerza.h"
#include "Particula.h"
#include "Vector3D.h"
#include "PxPhysicsAPI.h"
#include <iostream>

using namespace physx;

class ForceGenerator {
private:
    struct reg {
        Particula* p;
        TipoFuerza* tF;
        bool activa;
    };
    struct regRB {
        physx::PxRigidDynamic** rb;
        TipoFuerza* tF;
        bool activa;
    };

    std::vector<reg> registrosDeFuerzas;
    std::vector<regRB> registrosDeFuerzasRB;

public:
    void add(Particula* p, TipoFuerza* tF, bool activa)
    {
        registrosDeFuerzas.push_back({ p, tF , activa });
    }

    void quitar(Particula* p, TipoFuerza* tF)
    {
        registrosDeFuerzas.erase(std::remove_if(registrosDeFuerzas.begin(),
            registrosDeFuerzas.end(),
            [=](const reg& r) {
                return r.p == p &&
                    r.tF == tF;
            }),
            registrosDeFuerzas.end());
    }

    void borrarTodo() { registrosDeFuerzas.clear(); }
    void setActiva(TipoFuerza* tF, bool activa)
    {
        for (auto& r : registrosDeFuerzas) {
            if (r.tF == tF)
            {
                r.activa = activa;
            }
        }
    }
    void updateFuerzas(double dt)
    {
        for (auto& r : registrosDeFuerzas) {
            if (r.activa)
                r.tF->updateFuerza(r.p, dt);
        }
        for (auto& r : registrosDeFuerzasRB) {
            if (r.activa)
                r.tF->updateFuerzaRigidbody(*r.rb, dt);
        }
    }

    void updateUnaFuerza(Particula* p, double dt) {
        for (auto& r : registrosDeFuerzas) {
            if (r.p == p && r.activa)
                r.tF->updateFuerza(r.p, dt);
        }
    }
};