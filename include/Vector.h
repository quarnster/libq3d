#ifndef __INCLUDE_Q3D_VECTOR_H
#define __INCLUDE_Q3D_VECTOR_H

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3d-engine ;) (c) Outbreak 2001-2002        =
 * ===========================================================================
 *
 * @id		:	$Id: Vector.h,v 1.2 2004/01/28 20:14:26 quarn Exp $
 * @brief	:	A vector
 * @author	:	Fredrik Ehnbom
 *
 */

#include "Vertex.h"

typedef	q3dTypeVertex q3dTypeVector;

#define q3dVectorInit(a) q3dVertexInit(a)
#define q3dVectorSetV(a, b) q3dVertexSetV(a, b);
#define q3dVectorSet3f(a,b,c,d) q3dVertexSet3f(a,b,c,d)


void q3dVectorNormalize(q3dTypeVector *v);

// v = v * v2;
void q3dVectorCross(q3dTypeVector* v, q3dTypeVector *v2);

float q3dVectorDot(q3dTypeVector *v1, q3dTypeVector *v2);

#endif
