#ifndef __INCLUDED_Q3D_LEVEL_H
#define __INCLUDED_Q3D_LEVEL_H

#include <kos.h>

#include "Vertex.h"
#include "Texel.h"
#include "Vector.h"
#include "Polygon.h"

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3d-engine ;) (c) Outbreak 2001-2004        =
 * ===========================================================================
 *
 * @id		:	$Id: Level.h,v 1.1 2004/02/19 14:01:40 quarn Exp $
 * @brief	:	A level structure
 * @author	:	Fredrik "quarn" Ehnbom <quarn@home.se>
 *
 */

struct _q3dTypeLevel {
	q3dTypeTexel	*texel;			// texels for the vertices in the level

	uint32		vertexLength;		// number of vertices in the level
	q3dTypeVertex	*vertex;		// the vertex data

	uint32		polygonLength;		// the number of polygons in this level
	q3dTypePolygon	*polygon;		// the polygons
	q3dTypeVector	*_polygonNormal;	// an array with this polyhedrons polygonnormals
	q3dTypeVector	*_uPolygonNormal;	// the untranformed polygon normals
};
typedef struct _q3dTypeLevel q3dTypeLevel;

#endif
