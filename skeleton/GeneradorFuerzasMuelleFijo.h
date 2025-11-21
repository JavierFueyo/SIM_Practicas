#pragma once

#include "GeneradorFuerzasMuelle.h"
#include "core.hpp"

class GeneradorFuerzasMuelleFijo : public GeneradorFuerzasMuelle {
public:
	GeneradorFuerzasMuelleFijo(double k, double LargoEnReposo, const Vector3D& PosFijo) :
		GeneradorFuerzasMuelle(k, LargoEnReposo, nullptr) {
		_p = new Particula(PosFijo,Vector3D(0,0,0), Vector3D(0, 0, 0), Vector4(0, 0, 0,1),nullptr);
	}

	~GeneradorFuerzasMuelleFijo() { delete _p; }
};