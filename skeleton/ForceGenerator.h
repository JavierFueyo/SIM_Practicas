#pragma once
#include <vector>
#include <algorithm>
#include "TipoFuerza.h"
#include "Vector3D.h"
#include "PxPhysicsAPI.h"
#include <iostream>

using namespace physx;

class Particula;
class ForceGenerator {
private:
    struct reg {
        Particula* p;
        TipoFuerza* tF;
        bool activa;
    };
    struct regRB {
        PxRigidDynamic* rb;
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
    void addRB(PxRigidDynamic* rb, TipoFuerza* tF, bool activa)
    {
        registrosDeFuerzasRB.push_back({ rb, tF, activa});
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
    void quitarRB(PxRigidDynamic* rb, TipoFuerza* tF)
    {
        registrosDeFuerzasRB.erase(std::remove_if(registrosDeFuerzasRB.begin(),
            registrosDeFuerzasRB.end(),
            [=](const regRB& r) {
                return r.rb == rb &&
                    r.tF == tF;
            }),
            registrosDeFuerzasRB.end());
    }

    void borrarTodo() { 
        registrosDeFuerzas.clear();
        registrosDeFuerzasRB.clear();
    }

    void setActiva(TipoFuerza* tF, bool activa)
    {
        for (auto& r : registrosDeFuerzas) {
            if (r.tF == tF)
            {
                r.activa = activa;
            }
        }
        for (auto& r : registrosDeFuerzasRB) {
            if (r.tF == tF)
            {
                r.activa = activa;
            }
        }
    }

    void setActivaInd(PxRigidDynamic* rb, TipoFuerza* tF, bool activa) {
        for (auto& r : registrosDeFuerzasRB) {
            if (r.rb == rb && r.tF == tF)
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
                r.tF->updateFuerzaRigidbody(r.rb, dt);
        }
    }

    void updateUnaFuerza(Particula* p, double dt) {
        for (auto& r : registrosDeFuerzas) {
            if (r.p == p && r.activa)
                r.tF->updateFuerza(r.p, dt);
        }
    }
    void updateUnaFuerzaRB(PxRigidDynamic* rb, double dt) {
        for (auto& r : registrosDeFuerzasRB) {
            if (r.rb == rb && r.activa)
                r.tF->updateFuerzaRigidbody(r.rb, dt);
        }
    }
};