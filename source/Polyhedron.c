#include <kos.h>
#include "Polygon.h"
#include "Polyhedron.h"

void q3dPolyhedronInit(q3dTypePolyhedron *poly) {
	poly->_uVertexNormal = NULL;
	poly->_finalVertex = NULL;
	poly->vertex = NULL;
	poly->_vertexNormal = NULL;
	poly->vertexLength = 0;

	poly->texel = NULL;
	poly->polygon = NULL;
	poly->_uPolygonNormal = NULL;
	poly->_polygonNormal = NULL;
	poly->polygonLength = 0;

	q3dVertexInit(&poly->_pos);
	q3dAngleInit(&poly->_agl);
//	poly->positionTrack = NULL;
//	positionTrackLength = 0;
}

void q3dPolyhedronFree(q3dTypePolyhedron *poly) {
	if (poly->polygon != NULL) {
		int i;
		for (i = 0; i < poly->polygonLength; i++) {
			q3dPolygonFree(&poly->polygon[i]);
		}
		free(poly->polygon);
	}
	if (poly->_vertexNormal != NULL)	free(poly->_vertexNormal);
	if (poly->vertex != NULL)		free(poly->vertex);
	if (poly->_uVertexNormal != NULL)	free(poly->_uVertexNormal);
	if (poly->_finalVertex != NULL)		free(poly->_finalVertex);
	if (poly->_polygonNormal != NULL)	free(poly->_polygonNormal);
	if (poly->_uPolygonNormal != NULL)	free(poly->_uPolygonNormal);
	if (poly->texel != NULL)		free(poly->texel);

//	if (positionTrack != NULL) delete[] positionTrack;

	poly->vertexLength = poly->polygonLength /*= positionTrackLength*/ = 0;
}

void q3dPolyhedronUpdate(q3dTypePolyhedron *poly) {

//	if (poly->updateMatrix) {
		q3dMatrixIdentity();

		q3dMatrixTranslate(poly->_pos.x, poly->_pos.y, poly->_pos.z);
		q3dMatrixRotateX(poly->_agl.x);
		q3dMatrixRotateY(poly->_agl.y);
		q3dMatrixRotateZ(poly->_agl.z);


//		updateMatrix = false;
//		lastFrameUpdated = true;
//	} else {
//		lastFrameUpdated = false;
//	}
	q3dMatrixStore(&_q3dMatrixObject);
}

void q3dPolyhedronUpdateNormals(q3dTypePolyhedron *poly) {
	int i;
	for (i = 0; i < poly->polygonLength; i++) {
		q3dPolygonCalculateNormal(&poly->polygon[i], poly, &poly->_uPolygonNormal[i]);
	}

	for (i = 0; i < poly->vertexLength; i++) {
		int num = 0;

		poly->_uVertexNormal[i].x = 0;
		poly->_uVertexNormal[i].y = 0;
		poly->_uVertexNormal[i].z = 0;

		int j;
		for (j = 0; j < poly->polygonLength; j++) {
			int k;
			for (k = 0; k < poly->polygon[j].vertexLength; k++) {
				if (i == poly->polygon[j].vertex[k]) {
					poly->_uVertexNormal[i].x += poly->_uPolygonNormal[j].x;
					poly->_uVertexNormal[i].y += poly->_uPolygonNormal[j].y;
					poly->_uVertexNormal[i].z += poly->_uPolygonNormal[j].z;
					num++;
				}
			}
		}
		poly->_uVertexNormal[i].x /= num;
		poly->_uVertexNormal[i].y /= num;
		poly->_uVertexNormal[i].z /= num;
	}
}

void q3dPolyhedronCompile(q3dTypePolyhedron *poly) {
	if (poly->_finalVertex == NULL) {
		// first create the finalVertices
		poly->_finalVertex	= malloc(sizeof(pvr_vertex_t) * poly->vertexLength);
	
		// then calculate polygonnormals and vertex normals
		poly->_uPolygonNormal	= malloc(sizeof(q3dTypeVector) * poly->polygonLength);
		poly->_polygonNormal	= malloc(sizeof(q3dTypeVector) * poly->polygonLength);

		poly->_uVertexNormal	= malloc(sizeof(q3dTypeVector) * poly->vertexLength);
		poly->_vertexNormal	= malloc(sizeof(q3dTypeVector) * poly->vertexLength);

		q3dPolyhedronUpdateNormals(poly);
	}
}

void translate(float x, float y, float z)
{
    static float matrix[4][4] = {
	{ 1.0, 0.0, 0.0, 0.0 },
	{ 0.0, 1.0, 0.0, 0.0 },
	{ 0.0, 0.0, 1.0, 0.0 },
	{ 0.0, 0.0, 0.0, 1.0 },
    };

    matrix[3][0] = x;
    matrix[3][1] = y;
    matrix[3][2] = z;
    mat_apply(&matrix);
}

void q3dPolyhedronPaint(q3dTypePolyhedron *poly, q3dTypeCamera *cam, q3dTypeFiller *filler) {
	pvr_prim(&poly->material.header, sizeof(pvr_poly_hdr_t));

	q3dCameraUpdate(cam);
	q3dPolyhedronUpdate(poly);

//	if (cam->wasUpdated() || wasUpdated()) {
//		cam->project(this);
//		filler->update(this);
//	}

	q3dMatrixIdentity();
	q3dMatrixApply(&_q3dMatrixPerspective);
	q3dMatrixApply(&_q3dMatrixCamera);
	q3dMatrixApply(&_q3dMatrixObject);

	q3dMatrixTransformPVR(poly->vertex, &poly->_finalVertex[0].x, poly->vertexLength, sizeof(pvr_vertex_t));

	q3dMatrixIdentity();
	q3dMatrixApply(&_q3dMatrixCamera);
	q3dMatrixApply(&_q3dMatrixObject);
	q3dMatrixStore(&_q3dMatrixTemp);

	q3dMatrixTransformNormals(poly->_uVertexNormal, poly->_vertexNormal, poly->vertexLength);
	q3dMatrixTransformNormals(poly->_uPolygonNormal, poly->_polygonNormal, poly->polygonLength);

	filler->update(poly);
	filler->draw(poly);

}
/*
void Polyhedron::setRotation(const Point3D &p) {
	if (agl == p) return;
	agl = p;
	updateMatrix = true;
}

const Point3D &Polyhedron::getRotation() {
	return pos;
}
*/
/*
uint8 Polyhedron::behind(Polygon *p) {
	int i;
	for (i = 0; i < p->vertexLength; i++) {
		if (finalVertex[p->vertex[i]].z < 0) return 1;
	}
	return 0;
}
*/
