#ifndef __INCLUDED_Q3D_POLYHEDRON_H
#define __INCLUDED_Q3D_POLYHEDRON_H

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3d-engine ;) (c) Outbreak 2001-2002        =
 * ===========================================================================
 *
 * @id		:	$Id: Polyhedron.h,v 1.1 2004/01/24 21:41:43 quarn Exp $
 * @brief	:	Polyhedron methods and structure
 * @author	:	Fredrik Ehnbom
 *
 */

// #include "Point2D.h"
#include "Camera.h"
#include "Matrix.h"
#include "Polygon.h"
#include "Material.h"
#include "Vertex.h"
#include "Vector.h"
#include "Angle.h"
#include "Filler.h"
//#include "KeyFrame.h"
// #include "Object.h"

typedef struct _q3dTypePolyhedron q3dTypePolyhedron;

struct _q3dTypePolyhedron {
	q3dTypeAngle	_agl;
	q3dTypeVertex	_pos;

	q3dTypeTexel	*texel;
	q3dTypeVector	*_uPolygonNormal;
	q3dTypeVector	*_uVertexNormal;

	uint16		vertexLength;
	q3dTypeVertex	*vertex;
	q3dTypeVector	*_vertexNormal;

	pvr_vertex_t	*_finalVertex __attribute__((aligned(32)));

	q3dTypeMaterial	material;

	uint16		polygonLength;		// the number of polygons in this polyhedron
	struct _q3dTypePolygon	*polygon;	// the polygons
	q3dTypeVector	*_polygonNormal;	// an array with this polyhedrons polygonnormals
};

void q3dPolyhedronInit(q3dTypePolyhedron *poly);
void q3dPolyhedronFree(q3dTypePolyhedron *poly);

void q3dPolyhedronUpdate(q3dTypePolyhedron *poly);

void q3dPolyhedronCompile(q3dTypePolyhedron *poly);

//	void setRotation(const Point3D &agl);
//	const Point3D & getRotation();

struct _q3dTypeFiller;

void q3dPolyhedronPaint(q3dTypePolyhedron *poly, q3dTypeCamera *cam, struct _q3dTypeFiller *filler);

void q3dPolyhedronUpdateNormals(q3dTypePolyhedron *poly);

/*
namespace q3d {

class Polygon;
class Filler;
class Camera;
	
class Polyhedron : public Object {
friend class Camera;
protected:
	Point3D agl;			// the angle of this object

public:
	Point3D *_polygonNormal;	// the untranslated polygon normals
	Point3D *_vertexNormal;		// the untranslated vertex normals

	uint16 vertexLength;		// how many vertices there is in this polyhedron
	Point3D *vertex;		// the vertices
	Point3D *vNormal;		// the translated normals

	pvr_vertex_t *finalVertex;	// the final (ready to send to the pvr-chip) vertices

	Point3D pivot;			// the pivot of this object

	KeyFrame *positionTrack;	// Positiontrack keyframe for this object
	uint32 positionTrackLength;	// Length of the Positiontrack
	
	Material material;		// this polyhedrons material

	uint16 polygonLength;		// the number of polygons in this polyhedron
	Polygon *polygon;		// the polygons
	Point3D *pNormal;		// an array with this polyhedrons polygonnormals

	Polyhedron();
	~Polyhedron();

	void compile();

	void update();
	void setRotation(const Point3D &agl);
	const Point3D & getRotation();

	void paint(Camera *cam, Filler *filler);

	void createHeader(pvr_poly_cxt_t cxt);
	void updateNormals();
};

}
*/
#endif
