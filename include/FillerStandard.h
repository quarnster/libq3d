#ifndef __INCLUDED_Q3D_STANDARDFILLER_H
#define __INCLUDED_Q3D_STANDARDFILLER_H

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3D-engine ;) (c) Outbreak 2001-2002        =
 * ===========================================================================
 *
 * @id		:	$Id: FillerStandard.h,v 1.1 2004/01/24 21:41:43 quarn Exp $
 * @brief	:	standard goraud-filler..
 * @author	:	Fredrik "quarn" Ehnbom <quarn@home.se>
 *
 */
#include "Filler.h"

typedef q3dTypeFiller q3dTypeFillerStandard;

void q3dFillerStandardInit(q3dTypeFillerStandard *type);

void q3dFillerStandardUpdate(q3dTypePolyhedron *poly);
void q3dFillerStandardDraw(q3dTypePolyhedron *poly);

#endif
