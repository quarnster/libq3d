#ifndef __INCLUDED_Q3D_QUADTREE_H
#define __INCLUDED_Q3D_QUADTREE_H

#include "Quadnode.h"

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3d-engine ;) (c) Outbreak 2001-2004        =
 * ===========================================================================
 *
 * @id		:	$Id: Quadtree.h,v 1.1 2004/02/19 14:01:40 quarn Exp $
 * @brief	:	A quadtree
 * @author	:	Fredrik "quarn" Ehnbom <quarn@home.se>
 *
 */


typedef struct _q3dTypeQuadTree q3dTypeQuadTree;

struct _q3dTypeQuadTree {
	uint32		childCount;
	q3dTypeQuadNode *children;
};

void q3dQuadTreeInit(q3dTypeQuadTree *tree);

#endif
