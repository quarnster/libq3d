#ifndef __INCLUDED_Q3D_TEXTUREFILLER_H
#define __INCLUDED_Q3D_TEXTUREFILLER_H

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3D-engine ;) (c) Outbreak 2001-2002        =
 * ===========================================================================
 *
 * @id		:	$Id: FillerTexture.h,v 1.1 2004/01/24 21:41:43 quarn Exp $
 * @brief	:	Standard goraud/texture filler..
 * @author	:	Fredrik Ehnbom
 *
 */
#include "Filler.h"

typedef q3dTypeFiller q3dTypeFillerTexture;

void q3dFillerTextureInit(q3dTypeFillerTexture *type);

void q3dFillerTextureUpdate(q3dTypePolyhedron *poly);
void q3dFillerTextureDraw(q3dTypePolyhedron *poly);


#endif
