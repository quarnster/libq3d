#ifndef __INCLUDED_Q3D_ENVIRONMENTFILLER_H
#define __INCLUDED_Q3D_ENVIRONMENTFILLER_H

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3D-engine ;) (c) Outbreak 2001-2002        =
 * ===========================================================================
 *
 * @id		:	$Id: FillerEnvironment.h,v 1.1 2004/01/24 21:41:43 quarn Exp $
 * @brief	:	A filler that does Environment mapping
 * @author	:	Fredrik Ehnbom
 *
 */
#include "Filler.h"

typedef q3dTypeFiller q3dTypeFillerEnvironment;

void q3dFillerEnvironmentInit(q3dTypeFillerEnvironment *type);

void q3dFillerEnvironmentUpdate(q3dTypePolyhedron *poly);
void q3dFillerEnvironmentDraw(q3dTypePolyhedron *poly);

#endif
