#ifndef __INCLUDED_Q3D_FILLER_H
#define __INCLUDED_Q3D_FILLER_H

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3D-engine ;) (c) Outbreak 2001-2002        =
 * ===========================================================================
 *
 * @id		:	$Id: Filler.h,v 1.1 2004/01/24 21:41:43 quarn Exp $
 * @brief	:	A class which takes care of drawing a polyhedron
 * @author	:	Fredrik "quarn" Ehnbom <quarn@home.se>
 *
 */
#include <kos.h>
#include "Polygon.h"
#include "Polyhedron.h"

struct _q3dTypePolyhedron;

typedef void (*q3dTypeFillerUpdate)(struct _q3dTypePolyhedron *poly);
typedef void (*q3dTypeFillerDraw)(struct _q3dTypePolyhedron *poly);

typedef struct _q3dTypeFiller q3dTypeFiller;

struct _q3dTypeFiller {
	pvr_poly_cxt_t		defaultCxt;
	pvr_poly_hdr_t		defaultHeader;

	q3dTypeFillerUpdate	update;
	q3dTypeFillerDraw	draw;
};

#endif
