#ifndef __INCLUDED_Q3D_KEYFRAME_H
#define __INCLUDED_Q3D_KEYFRAME_H

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3D-engine ;) (c) Outbreak 2001-2002        =
 * ===========================================================================
 *
 * @id		:	$Id: Keyframe.h,v 1.1 2004/01/24 21:41:43 quarn Exp $
 * @brief	:	A keyframe class
 * @author	:	Fredrik "quarn" Ehnbom <quarn@home.se>
 *
 */
#include "Point3D.h"

namespace q3d {

class KeyFrame : public Point3D {
public:
	float time;

	Point3D tangent;
/*
	float x;
	float y;
	float z;
*/
	float tension;
	float continuity;
	float bias;

	KeyFrame();
//	KeyFrame(float x, float y, float z, float time);
//	KeyFrame(float x, float y, float z, float tension, float continuity, float bias, float time);

//	void set(float x, float y, float z, float tension, float continuity, float bias, float time);

};

}

#endif
