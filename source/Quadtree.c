#include "Quadtree.h"

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3d-engine ;) (c) Outbreak 2001-2004        =
 * ===========================================================================
 *
 * @id		:	$Id: Quadtree.c,v 1.1 2004/02/19 14:01:40 quarn Exp $
 * @brief	:	A quadtree
 * @author	:	Fredrik "quarn" Ehnbom <quarn@home.se>
 *
 */

void q3dQuadTreeInit(q3dTypeQuadTree *tree) {
	tree->childCount = 0;
	tree->children = NULL;
}

