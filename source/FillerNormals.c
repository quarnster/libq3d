#include "NormalFiller.h"

#define CLAMP(a) a < 0 ? 0 : a > 0.8 ? 0.8 : a
namespace q3d {

NormalFiller::NormalFiller() {
	// for the line
	pvr_poly_cxt_t lineCxt;
	pvr_poly_cxt_col(&lineCxt, PVR_LIST_OP_POLY);
	lineCxt.gen.culling = PVR_CULLING_NONE;
//	lineCxt.depth.write = PVR_DEPTHWRITE_DISABLE;
//	lineCxt.depth.comparison = PVR_DEPTHCMP_GEQUAL;
	pvr_poly_compile(&lineHdr, &lineCxt);
}

void NormalFiller::update(Polyhedron *poly) {
}

void NormalFiller::drawLine(Point3D *p1, Point3D *p2, float thickness) {
	// create lineVector
	Point3D lineVector(p1->x - p2->x, p1->y - p2->y, p1->z - p2->z);
	lineVector.normalize();

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
	vert.x = p1->x + lineVector.x;
	vert.y = p1->y + lineVector.y;
	vert.z = p1->z;
	pvr_prim(&vert, sizeof(pvr_vertex_t));

	// bottom left
	vert.x = p1->x - lineVector.x;
	vert.y = p1->y - lineVector.y;
	vert.z = p1->z;
	pvr_prim(&vert, sizeof(pvr_vertex_t));

	// top right
	vert.x = p2->x + lineVector.x;
	vert.y = p2->y + lineVector.y;
	vert.z = p1->z;
	pvr_prim(&vert, sizeof(pvr_vertex_t));

	// bottom right;
	vert.flags = PVR_CMD_VERTEX_EOL;
	vert.x = p2->x - lineVector.x;
	vert.y = p2->y - lineVector.y;
	vert.z = p1->z;
	pvr_prim(&vert, sizeof(pvr_vertex_t));
}

void NormalFiller::draw(Polyhedron *poly) {
	pvr_prim(&lineHdr, sizeof(pvr_poly_hdr_t));

	for (int i = 0; i < poly->vertexLength; i++) {
		Point3D p1(
			poly->finalVertex[i].x,
			poly->finalVertex[i].y,
			poly->finalVertex[i].z
		);

		Point3D p2(
			poly->finalVertex[i].x + poly->vNormal[i].x*15,
			poly->finalVertex[i].y + poly->vNormal[i].y*15,
			1/(1/poly->finalVertex[i].z +poly->vNormal[i].z*15)
		);
		drawLine(&p1, &p2, 1);
	}
}

}

