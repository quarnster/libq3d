#ifndef __INCLUDED_Q3D_MATERIAL_H
#define __INCLUDED_Q3D_MATERIAL_H

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3d-engine ;) (c) Outbreak 2001-2002        =
 * ===========================================================================
 *
 * @id		:	$Id: Material.h,v 1.1 2004/01/24 21:41:43 quarn Exp $
 * @brief	:	Polyhedron Material
 * @author	:	Fredrik Ehnbom
 *
 */

#include "Color.h"
#include "Texture.h"

typedef struct {
	q3dTypeColor	color;		// color of material
	q3dTypeTexture	texture;	// texture of material
	pvr_poly_hdr_t	header;		// the "header" to send to the pvr2-chip
} q3dTypeMaterial;

#endif
