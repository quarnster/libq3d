#ifndef __INCLUDED_Q3D_CELLFILLER_H
#define __INCLUDED_Q3D_CELLFILLER_H

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3D-engine ;) (c) Outbreak 2001-2002        =
 * ===========================================================================
 *
 * @id		:	$Id: FillerCell.h,v 1.1 2004/01/24 21:41:43 quarn Exp $
 * @brief	:	A filler that does Cellshading
 * @author	:	Fredrik "quarn" Ehnbom <quarn@home.se"
 *
 */
#include "Filler.h"
#include <kos.h>

typedef q3dTypeFiller q3dTypeFillerCell;

void q3dFillerCellInit(q3dTypeFillerCell *type);

// void q3dFillerCelldrawLine(q3dTypePolyhedron *poly);
void q3dFillerCellUpdate(q3dTypePolyhedron *poly);
void q3dFillerCellDraw(q3dTypePolyhedron *poly);

#endif
