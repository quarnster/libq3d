#include <kos.h>
#include "Polygon.h"

void q3dPolygonInit(q3dTypePolygon *poly) {
	poly->flags = 0;
	poly->vertexLength = 0;
	poly->vertex = NULL;
	poly->texel = NULL;
}

void q3dPolygonFree(q3dTypePolygon *poly) {
	if (poly->vertex != NULL) free(poly->vertex);
	if (poly->texel != NULL) free(poly->texel);
	poly->vertexLength = 0;
	poly->texel = NULL;
	poly->vertex = NULL;
}

void q3dPolygonCalculateNormal(q3dTypePolygon *poly, q3dTypePolyhedron *ph, q3dTypeVector *p) {
	float length;
	q3dTypeVector *p1 = &ph->vertex[poly->vertex[0]];
	q3dTypeVector *p2 = &ph->vertex[poly->vertex[1]];
	q3dTypeVector *p3 = &ph->vertex[poly->vertex[2]];

	p->x = ((p1->y - p2->y) * (p1->z - p3->z)) - ((p1->z - p2->z) * (p1->y - p3->y));
	p->y = ((p1->z - p2->z) * (p1->x - p3->x)) - ((p1->x - p2->x) * (p1->z - p3->z));
	p->z = ((p1->x - p2->x) * (p1->y - p3->y)) - ((p1->y - p2->y) * (p1->x - p3->x));

	length = fsqrt((p->x * p->x) + (p->y * p->y) + (p->z * p->z));
	p->x /= length;
	p->y /= length;
	p->z /= length;
}
