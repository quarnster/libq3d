#ifndef __INCLUDED_Q3D_PLANE_H
#define __INCLUDED_Q3D_PLANE_H

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3d-engine ;) (c) Outbreak 2001-2004        =
 * ===========================================================================
 *
 * @id		:	$Id: Plane.h,v 1.2 2004/03/18 09:52:28 quarn Exp $
 * @brief	:	Plane
 * @author	:	Fredrik "quarn" Ehnbom <quarn@home.se>
 *
 */

typedef struct {
	float a;
	float b;
	float c;
	float d;
} q3dTypePlane;

inline float q3dPlanePointInPlane(q3dTypePlane *plane, q3dTypeVector *point) {
	return plane->a * point->x + plane->b * point->y + plane->c * point->z + plane->d;
}

inline void q3dPlaneNormalize(q3dTypePlane *plane) {
	float mag = frsqrt(plane->a * plane->a + plane->b * plane->b + plane->c * plane->c);
	plane->a *= mag;
	plane->b *= mag;
	plane->c *= mag;
	plane->d *= mag;
}

#endif
