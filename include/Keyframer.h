#ifndef __INCLUDED_Q3D_KEYFRAMER_H
#define __INCLUDED_Q3D_KEYFRAMER_H

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3D-engine ;) (c) Outbreak 2001-2002        =
 * ===========================================================================
 *
 * @id		:	$Id: Keyframer.h,v 1.1 2004/01/24 21:41:43 quarn Exp $
 * @brief	:	Keyframer. handles keyframing
 * @author	:	Fredrik "quarn" Ehnbom <quarn@home.se>
 *
 */
#include <kos.h>
#include "KeyFrame.h"

namespace q3d {

class KeyFramer {
public:
	static void generate(KeyFrame *track, uint32 length);
	static void getv(KeyFrame *track, uint32 length, Point3D *target, bool anStuff, uint32 n);

	static void getKey(KeyFrame *keys, uint32 length, Point3D *target, float time);
};

}

#endif

