#ifndef __INCLUDED_Q3D_H
#define __INCLUDED_Q3D_H

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3D-engine ;) (c) Outbreak 2001-2002        =
 * ===========================================================================
 *
 * @id		:	$Id: q3d.h,v 1.1 2004/01/24 21:41:43 quarn Exp $
 * @brief	:	Main include-file for q3d. This should be the only
 *			file that users include in their projects. 
 * @author	:	Fredrik "quarn" Ehnbom <quarn@home.se>
 *
 */

#include <kos.h>

#ifdef __cplusplus
extern "C" {
#endif

// keyframing
//#include "KeyFrame.h"
//#include "KeyFramer.h"

// objects
//#include "Object.h"
#include "Polyhedron.h"
#include "Polygon.h"
#include "Camera.h"

// fillers
#include "Filler.h"
#include "FillerCell.h"
#include "FillerEnvironment.h"
#include "FillerStandard.h"
#include "FillerTexture.h"
#include "FillerWireframe.h"
//#include "NormalFiller.h"


// data
#include "Vertex.h"
#include "Vector.h"
#include "Angle.h"
#include "Texel.h"
#include "Material.h"
#include "Texture.h"
#include "Color.h"

// general
#include "Matrix.h"
// #include "Load3DS.h"

#ifdef __cplusplus
}
#endif

#endif
