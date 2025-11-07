#include "Ground.h"

Ground::Ground(float size) {
	PxBoxGeometry floor(size, 1, size/2);
	renderItem = new RenderItem(CreateShape(floor, gMaterial), Vector4(0, 1, 0, 1));
}