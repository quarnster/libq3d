#include "FillerEnvironment.h"

void q3dFillerEnvironmentInit(q3dTypeFillerEnvironment *type) {
	pvr_poly_cxt_txr(
		&type->defaultCxt, PVR_LIST_OP_POLY,
		PVR_TXRFMT_RGB565 | PVR_TXRFMT_NONTWIDDLED,
		256, 256,
		0,
		PVR_FILTER_BILINEAR
	);
	pvr_poly_compile(&type->defaultHeader, &type->defaultCxt);
	type->update = &q3dFillerEnvironmentUpdate;
	type->draw = &q3dFillerEnvironmentDraw;

}

void q3dFillerEnvironmentUpdate(q3dTypePolyhedron *poly) {
	int i  = poly->vertexLength;
	while (i--) {
		float shade =  (-poly->_vertexNormal[i].z-0.5f);

		float a = poly->material.color.a;// + shade;
		float r = poly->material.color.r/* + shade*/;
		float g = poly->material.color.g/* + shade*/;
		float b = poly->material.color.b/* + shade*/;

		r = r > 1.0f ? 1.0f : r < 0.0f ? 0.0f : r;
		g = g > 1.0f ? 1.0f : g < 0.0f ? 0.0f : g;
		b = b > 1.0f ? 1.0f : b < 0.0f ? 0.0f : b;
		poly->_finalVertex[i].argb = PVR_PACK_COLOR(a, r, g, b);

		poly->_finalVertex[i].u = 0.5f + poly->_vertexNormal[i].x * 0.5f;
		poly->_finalVertex[i].v = 0.5f + poly->_vertexNormal[i].y * 0.5f;
	}
}

void q3dFillerEnvironmentDraw(q3dTypePolyhedron *poly) {
	int i;

	pvr_vertex_t *vert;
	pvr_vertex_t *vert2;
	pvr_dr_state_t state;
	pvr_dr_init(state);

	for (i = 0; i < poly->polygonLength; i++) {
		int j;

		int len = poly->polygon[i].vertexLength-1;

		for (j = 0; j < len; j++) {
			vert2 = &poly->_finalVertex[poly->polygon[i].vertex[j]];
			vert = pvr_dr_target(state);
			vert->flags = PVR_CMD_VERTEX;
			vert->x = vert2->x;
			vert->y = vert2->y;
			vert->z = vert2->z;
			vert->u = vert2->u;
			vert->v = vert2->v;
			vert->argb = vert2->argb;
			pvr_dr_commit(vert);
		}
		vert2 = &poly->_finalVertex[poly->polygon[i].vertex[len]];
		vert = pvr_dr_target(state);
		vert->flags = PVR_CMD_VERTEX_EOL;
		vert->x = vert2->x;
		vert->y = vert2->y;
		vert->z = vert2->z;
		vert->u = vert2->u;
		vert->v = vert2->v;
		vert->argb = vert2->argb;
		pvr_dr_commit(vert);
	}
}
