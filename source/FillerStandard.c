#include "FillerStandard.h"


void q3dFillerStandardInit(q3dTypeFillerStandard *filler) {
	pvr_poly_cxt_col(&filler->defaultCxt, PVR_LIST_OP_POLY);
	pvr_poly_compile(&filler->defaultHeader, &filler->defaultCxt);

	filler->update = &q3dFillerStandardUpdate;
	filler->draw = &q3dFillerStandardDraw;

}

void q3dFillerStandardUpdate(q3dTypePolyhedron *poly) {
	int i;
	for (i = 0; i < poly->vertexLength; i++) {
		float shade =  (-poly->_vertexNormal[i].z*0.75f-0.5f);

		float a = poly->material.color.a;
		float r = poly->material.color.r + shade;
		float g = poly->material.color.g + shade;
		float b = poly->material.color.b + shade;

		r = r > 1.0f ? 1.0f : r < 0.0f ? 0.0f : r;
		g = g > 1.0f ? 1.0f : g < 0.0f ? 0.0f : g;
		b = b > 1.0f ? 1.0f : b < 0.0f ? 0.0f : b;
		poly->_finalVertex[i].argb = PVR_PACK_COLOR(a, r, g, b);		
	}
}

void q3dFillerStandardDraw(q3dTypePolyhedron *poly) {
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

