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
	int i;
	for (i = 0; i < poly->vertexLength; i++) {
		float shade =  (-poly->_vertexNormal[i].z-0.5f);

		float a = poly->material.color.a;// + shade;
		float r = poly->material.color.r + shade;
		float g = poly->material.color.g + shade;
		float b = poly->material.color.b + shade;

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
	for (i = 0; i < poly->polygonLength; i++) {

		int len = poly->polygon[i].vertexLength-1;
		int j;
		for (j = 0; j < len; j++) {
			poly->_finalVertex[poly->polygon[i].vertex[j]].flags = PVR_CMD_VERTEX;
			pvr_prim(&poly->_finalVertex[poly->polygon[i].vertex[j]], sizeof(pvr_vertex_t));
		}
		poly->_finalVertex[poly->polygon[i].vertex[len]].flags = PVR_CMD_VERTEX_EOL;
		pvr_prim(&poly->_finalVertex[poly->polygon[i].vertex[len]], sizeof(pvr_vertex_t));
	}
}
