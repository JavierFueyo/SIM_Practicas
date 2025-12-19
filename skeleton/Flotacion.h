#pragma once

#include "ForceGenerator.h"
#include "core.hpp"
extern PxMaterial* gMaterial;

class Flotacion : public TipoFuerza {
public:
	//Altura = alto partícula; h0 = altura borde líquido; h = altura particula
	Flotacion(float Altura, float Volumen, float Densidad,
		float x0, float x1, float z0, float z1, float h0 = 0.0f) :
		_altura(Altura), _volumen(Volumen), _densidadLiquido(Densidad),
		_x0(x0), _x1(x1), _z0(z0), _z1(z1), _h0(h0)
	{
		/*PxBoxGeometry floor(_x1 - _x0, h0, _z1 - _z0);*/
		transform = PxTransform((_x0 + (_x1 - _x0) / 2.0f), _h0, (_z0 + (_z1 - _z0) / 2.0f));
		PxBoxGeometry geometry((_x1 - _x0) / 2.0f, _altura, (_z1 - _z0) / 2.0f);
		renderItem = new RenderItem(CreateShape(geometry, gMaterial), &transform, Vector4(0, 0, 1, 1));
	}

	virtual ~Flotacion() {
		if (renderItem) {
			DeregisterRenderItem(renderItem);
			delete renderItem;
			renderItem = nullptr;
		}
	}

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

	virtual void updateFuerzaRigidbody(physx::PxRigidDynamic* rigidbody, double t) override {
		if (rigidbody->getGlobalPose().p.x > _x0 && rigidbody->getGlobalPose().p.x < _x1
			&& rigidbody->getGlobalPose().p.z > _z0 && rigidbody->getGlobalPose().p.z < _z1) {
			float h = rigidbody->getGlobalPose().p.y;

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
			rigidbody->addForce(PxVec3(f.X(), f.Y(), f.Z()));
		}

	}


	inline void setDens(float Densidad) { _densidadLiquido = Densidad; }

	FUERZAS getTipo() { return _tipo; }
protected:
	float _altura;
	float _volumen;
	float _densidadLiquido;
	float _x0, _x1, _z0, _z1;
	float _gravedad = 9.8;
	float _h0;
	PxTransform transform;
	RenderItem* renderItem;

	FUERZAS _tipo = FUERZAS::FLOTACION;
};