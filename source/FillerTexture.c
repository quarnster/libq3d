#include "FillerTexture.h"

void q3dFillerTextureInit(q3dTypeFillerTexture *type) {
	pvr_poly_cxt_txr(
		&type->defaultCxt, PVR_LIST_OP_POLY,
		PVR_TXRFMT_RGB565 | PVR_TXRFMT_NONTWIDDLED,
		256, 256,
		0,
		PVR_FILTER_BILINEAR
	);
	pvr_poly_compile(&type->defaultHeader, &type->defaultCxt);
	type->update = &q3dFillerTextureUpdate;
	type->draw = &q3dFillerTextureDraw;

}

void q3dFillerTextureUpdate(q3dTypePolyhedron *poly) {
	int i;
	for (i = 0; i < poly->vertexLength; i++) {
		float shade =  (-poly->_vertexNormal[i].z-0.5f);

		float a = poly->material.color.a; // + shade;
		float r = poly->material.color.r + shade;
		float g = poly->material.color.g + shade;
		float b = poly->material.color.b + shade;

		r = r > 1.0f ? 1.0f : r < 0.0f ? 0.0f : r;
		g = g > 1.0f ? 1.0f : g < 0.0f ? 0.0f : g;
		b = b > 1.0f ? 1.0f : b < 0.0f ? 0.0f : b;
		poly->_finalVertex[i].argb = PVR_PACK_COLOR(a, r, g, b);	
	}
}

void q3dFillerTextureDraw(q3dTypePolyhedron *poly) {
	int i;
	for (i = 0; i < poly->polygonLength; i++) {
		int len = poly->polygon[i].vertexLength-1;
		int j;
		int pos;

		for (j = 0; j < len; j++) {
			pos = poly->polygon[i].vertex[j];
				
			poly->_finalVertex[pos].flags = PVR_CMD_VERTEX;
			poly->_finalVertex[pos].u = poly->polygon[i].texel[j].u;
			poly->_finalVertex[pos].v = poly->polygon[i].texel[j].v;
				
			pvr_prim(&poly->_finalVertex[pos], sizeof(pvr_vertex_t));
		}
		pos = poly->polygon[i].vertex[len];

		poly->_finalVertex[pos].flags = PVR_CMD_VERTEX_EOL;
		poly->_finalVertex[pos].u = poly->polygon[i].texel[len].u;
		poly->_finalVertex[pos].v = poly->polygon[i].texel[len].v;
		pvr_prim(&poly->_finalVertex[pos], sizeof(pvr_vertex_t));
	}
}
