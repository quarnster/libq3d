#ifndef __INCLUDED_Q3D_WIREFRAMEFILLER_H
#define __INCLUDED_Q3D_WIREFRAMEFILLER_H

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3D-engine ;) (c) Outbreak 2001-2002        =
 * ===========================================================================
 *
 * @id		:	$Id: FillerWireframe.h,v 1.1 2004/01/24 21:41:43 quarn Exp $
 * @brief	:	Standard wireframe filler..
 * @author	:	Fredrik Ehnbom
 *
 */
#include "Filler.h"

typedef q3dTypeFiller q3dTypeFillerWireframe;

void q3dFillerWireframeInit(q3dTypeFillerWireframe *type);

void q3dFillerWireframeDrawLine(pvr_vertex_t *p1, pvr_vertex_t *p2, float thickness);
void q3dFillerWireframeUpdate(q3dTypePolyhedron *poly);
void q3dFillerWireframeDraw(q3dTypePolyhedron *poly);

#endif
