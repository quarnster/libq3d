#ifndef __INCLUDE_Q3D_VECTOR_H
#define __INCLUDE_Q3D_VECTOR_H

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3d-engine ;) (c) Outbreak 2001-2002        =
 * ===========================================================================
 *
 * @id		:	$Id: Vector.h,v 1.1 2004/01/24 21:41:43 quarn Exp $
 * @brief	:	A vector
 * @author	:	Fredrik Ehnbom
 *
 */

#include "Vertex.h"

typedef	q3dTypeVertex q3dTypeVector;

#define q3dVectorInit(a) q3dVertexInit(a)
#define q3dVectorSet3f(a,b,c,d) q3dVertexSet3f(a,b,c,d)

void q3dVectorNormalize(q3dTypeVector *v);

// v = v * v2;
void q3dVectorCross(q3dTypeVector* v, q3dTypeVector *v2);

#endif
