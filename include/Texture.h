#ifndef __INCLUDED_Q3D_TEXTURE_H
#define __INCLUDED_Q3D_TEXTURE_H

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3d-engine ;) (c) Outbreak 2001-2002        =
 * ===========================================================================
 *
 * @id		:	$Id: Texture.h,v 1.1 2004/01/24 21:41:43 quarn Exp $
 * @brief	:	Texture-structure
 * @author	:	Fredrik Ehnbom
 *
 */
#include <kos.h>

typedef struct {
	uint32 mode;	// the colorformat for this texture
	uint16 width;	// width of texture
	uint16 height;	// height of texture
	pvr_ptr_t addr;	// the textures address
	uint8 filter;	// filtering type
} q3dTypeTexture;

#endif
