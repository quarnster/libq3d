#ifndef __INCLUDE_Q3D_ANGLE_H
#define __INCLUDE_Q3D_ANGLE_H
 
/**
 ** ===========================================================================
 ** = Q3D - quarns quick and dirty 3d-engine ;) (c) Outbreak 2001-2002        =
 ** ===========================================================================
 **
 ** @id          :       $Id: Angle.h,v 1.1 2004/01/24 21:41:43 quarn Exp $
 ** @brief       :       A rotating angle
 ** @author      :       Fredrik Ehnbom
 **
 **/
 
#include "Vertex.h"
 
typedef q3dTypeVertex q3dTypeAngle;
 
#define q3dAngleInit(a)         q3dVertexInit(a)
#define q3dAngleEquals(a,b)     q3dVertexEquals(a,b)
#define q3dAngleSetV(a,b)       q3dVertexSetV(a,b)
 
#endif

