/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3D-engine ;) (c) Outbreak 2001-2003        =
 * ===========================================================================
 *
 * @id		:	$Id: FillerCell.c,v 1.1 2004/01/24 21:41:43 quarn Exp $
 * @brief	:	A filler that does Cellshading
 * @author	:	Fredrik "quarn" Ehnbom <quarn@home.se"
 *
 */

#include "FillerCell.h"

#define CLAMP(a) a < 0 ? 0 : a > 0.8 ? 0.8 : a

void q3dFillerCellInit(q3dTypeFillerCell *type) {
	unsigned char cellTable[16] = {
		0x80, 0x80, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
	};

	unsigned short ctCopy[64*8];
	int y;
	for (y = 0; y < 8; y++) {
		int x;
		for (x = 0; x < 64; x++) {
			ctCopy[y * 64 + x] = 
				(cellTable[x>>2] >> 3) << 11 |
				(cellTable[x>>2] >> 2) << 5 |
				(cellTable[x>>2] >> 3);
		}
	}

	pvr_ptr_t ptr = pvr_mem_malloc(64 * 8 * 2);

	pvr_txr_load(&ctCopy, ptr, 64 * 8 * 2);

	pvr_poly_cxt_txr(
		&type->defaultCxt, PVR_LIST_OP_POLY,
		PVR_TXRFMT_RGB565 | PVR_TXRFMT_NONTWIDDLED,
		64, 8,
		ptr,
		PVR_FILTER_NEAREST
	);
	pvr_poly_compile(&type->defaultHeader, &type->defaultCxt);
	type->update = &q3dFillerCellUpdate;
	type->draw = &q3dFillerCellDraw;

}


void q3dFillerCellUpdate(q3dTypePolyhedron *poly) {
	int i;
	for (i = 0; i < poly->vertexLength; i++) {
		float shade =  -poly->_vertexNormal[i].z;
		shade = CLAMP(shade);

		float a = poly->material.color.a;
		float r = poly->material.color.r;
		float g = poly->material.color.g;
		float b = poly->material.color.b;

		poly->_finalVertex[i].argb = PVR_PACK_COLOR(a, r, g, b);
		poly->_finalVertex[i].u = shade;
		poly->_finalVertex[i].v = 1;
	}
}

void q3dFillerCellDraw(q3dTypePolyhedron *poly) {
	int i;

	for (i = 0; i < poly->polygonLength; i++) {
//		if (poly->pNormal[i].z > 0) continue;
		int j;

		int len = poly->polygon[i].vertexLength-1;

		for (j = 0; j < len; j++) {
			poly->_finalVertex[poly->polygon[i].vertex[j]].flags = PVR_CMD_VERTEX;
			pvr_prim(&poly->_finalVertex[poly->polygon[i].vertex[j]], sizeof(pvr_vertex_t));
		}
		poly->_finalVertex[poly->polygon[i].vertex[len]].flags = PVR_CMD_VERTEX_EOL;
		pvr_prim(&poly->_finalVertex[poly->polygon[i].vertex[len]], sizeof(pvr_vertex_t));
	}
}
