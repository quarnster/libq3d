#ifndef __INCLUDED_Q3D_POLYGON_H
#define __INCLUDED_Q3D_POLYGON_H

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3d-engine ;) (c) Outbreak 2001-2002        =
 * ===========================================================================
 *
 * @id		:	$Id: Polygon.h,v 1.1 2004/01/24 21:41:43 quarn Exp $
 * @brief	:	Polygon structure and methods
 * @author	:	Fredrik "quarn" Ehnbom <quarn@home.se>
 *
 */

#include "Texel.h"
#include "Vertex.h"
#include "Vector.h"
#include "Polyhedron.h"

typedef struct _q3dTypePolygon q3dTypePolygon;

struct _q3dTypePolygon {
	uint16		vertexLength;
	uint16		*vertex;
	q3dTypeTexel	*texel;
};

struct _q3dTypePolyhedron;

void q3dPolygonInit(q3dTypePolygon *poly);
void q3dPolygonFree(q3dTypePolygon *poly);
void q3dPolygonCalculateNormal(q3dTypePolygon *poly, struct _q3dTypePolyhedron *ph, q3dTypeVector *normal);


#endif
