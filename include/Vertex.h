#ifndef __INCLUDE_Q3D_VERTEX_H
#define __INCLUDE_Q3D_VERTEX_H

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3d-engine ;) (c) Outbreak 2001-2002        =
 * ===========================================================================
 *
 * @id		:	$Id: Vertex.h,v 1.1 2004/01/24 21:41:43 quarn Exp $
 * @brief	:	Represents a point in 3d-space (x, y, z)
 * @author	:	Fredrik Ehnbom
 *
 */


typedef struct {
	float x;
	float y;
	float z;
} q3dTypeVertex;


void q3dVertexSetV(q3dTypeVertex *v, q3dTypeVertex *v2);
void q3dVertexSet3f(q3dTypeVertex *v, float x, float y, float z);
void q3dVertexInit(q3dTypeVertex *v);

// ret (v == v2)
int q3dVertexEquals(q3dTypeVertex *v, q3dTypeVertex *v2);

// v = v + v2;
void q3dVertexAdd(q3dTypeVertex *v, q3dTypeVertex *v2);
// v = v - v2;
void q3dVertexSub(q3dTypeVertex *v, q3dTypeVertex *v2);

#endif
