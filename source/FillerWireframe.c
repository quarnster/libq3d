#include "FillerWireframe.h"

void q3dFillerWireframeInit(q3dTypeFillerWireframe *type) {
	pvr_poly_cxt_col(&type->defaultCxt, PVR_LIST_OP_POLY);
	pvr_poly_compile(&type->defaultHeader, &type->defaultCxt);

	type->update = &q3dFillerWireframeUpdate;
	type->draw = &q3dFillerWireframeDraw;


}

void q3dFillerWireframeUpdate(q3dTypePolyhedron *poly) {
	// not needed...
}

void q3dFillerWireframeDrawLine(pvr_vertex_t *p1, pvr_vertex_t *p2, float thickness) {
	// create lineVector
	q3dTypeVector lineVector;
	q3dVectorSet3f(&lineVector, p1->x - p2->x, p1->y - p2->y, p1->z - p2->z);
	q3dVectorNormalize(&lineVector);

	// rotate 90 degrees
	float tmp = lineVector.y;
	lineVector.y = lineVector.x;
	lineVector.x = -tmp;

	// apply thickness
	lineVector.x *= thickness/2;
	lineVector.y *= thickness/2;

	// draw
	pvr_vertex_t vert;
	vert.argb = PVR_PACK_COLOR(1, 0, 0, 0);

	// top left
	vert.flags = PVR_CMD_VERTEX;
	vert.x = p1->x - lineVector.x;
	vert.y = p1->y - lineVector.y;
	vert.z = p1->z;
	pvr_prim(&vert, sizeof(pvr_vertex_t));

	// bottom left
	vert.x = p1->x + lineVector.x;
	vert.y = p1->y + lineVector.y;
	vert.z = p1->z;
	pvr_prim(&vert, sizeof(pvr_vertex_t));

	// top right
	vert.x = p2->x - lineVector.x;
	vert.y = p2->y - lineVector.y;
	vert.z = p2->z;
	pvr_prim(&vert, sizeof(pvr_vertex_t));

	// bottom right;
	vert.flags = PVR_CMD_VERTEX_EOL;
	vert.x = p2->x + lineVector.x;
	vert.y = p2->y + lineVector.y;
	vert.z = p2->z;
	pvr_prim(&vert, sizeof(pvr_vertex_t));
}
void q3dFillerWireframeDraw(q3dTypePolyhedron *poly) {
	int i;
	for (i = 0; i < poly->polygonLength; i++) {
		int len = poly->polygon[i].vertexLength-1;
		int j;

		if (poly->_polygonNormal[i].z >= 0) continue;

		for (j = 0; j < len; j++) {
			pvr_vertex_t *p1 = &poly->_finalVertex[poly->polygon[i].vertex[j]];
			pvr_vertex_t *p2 = &poly->_finalVertex[poly->polygon[i].vertex[j+1]];
			q3dFillerWireframeDrawLine(p1, p2, 1);
		}
//		pvr_vertex_t *p1 = &poly->_finalVertex[poly->polygon[i].vertex[len]];
//		pvr_vertex_t *p2 = &poly->_finalVertex[poly->polygon[i].vertex[0]];
//		q3dFillerWireframeDrawLine(p1, p2, 1);
	}
}
