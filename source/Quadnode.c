#include "Quadnode.h"

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3d-engine ;) (c) Outbreak 2001-2004        =
 * ===========================================================================
 *
 * @id		:	$Id: Quadnode.c,v 1.1 2004/02/19 14:01:40 quarn Exp $
 * @brief	:	A node for a quadtree
 * @author	:	Fredrik "quarn" Ehnbom <quarn@home.se>
 *
 */

void q3dQuadNodeInit(q3dTypeQuadNode *node) {
	node->child[0] = node->child[1] = node->child[2] = node->child[3] = -1;
	q3dVectorInit(&node->position);
	node->polygonLength = 0;
	node->polygon = NULL;
}

