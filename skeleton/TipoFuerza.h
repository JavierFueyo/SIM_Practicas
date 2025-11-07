#pragma once

class Particula;
class TipoFuerza {
public:
	virtual ~TipoFuerza() = default;
	virtual void updateFuerza(Particula* p, double t) = 0;
};