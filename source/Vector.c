#include <kos.h>
#include "Vector.h"

void q3dVectorNormalize(q3dTypeVector *v) {
	float len = fsqrt(v->x*v->x+v->y*v->y+v->z*v->z);
	v->x /= len;
	v->y /= len;
	v->z /= len;
}

float q3dVectorDot(q3dTypeVector *v1, q3dTypeVector *v2) {
	return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

void q3dVectorCross(q3dTypeVector *v1, q3dTypeVector *v2) {
	float x = v1->y * v2->z - v1->z * v2->y;
	float y = v1->z * v2->x - v1->x * v2->z;
	float z = v1->x * v2->y - v1->y * v2->x;
	v1->x = x;
	v1->y = y;
	v1->z = z;
}

