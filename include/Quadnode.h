#ifndef __INCLUDED_Q3D_QUADNODE_H
#define __INCLUDED_Q3D_QUADNODE_H

#include <kos.h>

#include "Vector.h"

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3d-engine ;) (c) Outbreak 2001-2004        =
 * ===========================================================================
 *
 * @id		:	$Id: Quadnode.h,v 1.1 2004/02/19 14:01:40 quarn Exp $
 * @brief	:	A node for a quadtree
 * @author	:	Fredrik "quarn" Ehnbom <quarn@home.se>
 *
 */


typedef struct _q3dTypeQuadNode q3dTypeQuadNode;

struct _q3dTypeQuadNode {
	uint32		child[4];
	float		radius;
	q3dTypeVector	position;
	uint32		polygonLength;
	uint32		*polygon;
};

struct _q3dTypePolyhedron;

void q3dQuadNodeInit(q3dTypeQuadNode *node);

#endif
