#include <kos.h>
#include "Vector.h"

void q3dVectorNormalize(q3dTypeVector *v) {
	float len = fsqrt(v->x*v->x+v->y*v->y+v->z*v->z);
	v->x /= len;
	v->y /= len;
	v->z /= len;
}

