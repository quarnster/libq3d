#ifndef __INCLUDED_Q3D_OBJECT_H
#define __INCLUDED_Q3D_OBJECT_H

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3d-engine ;) (c) Outbreak 2001-2002        =
 * ===========================================================================
 *
 *
 * @id		:	$Id: Object.h,v 1.1 2004/01/24 21:41:43 quarn Exp $
 * @brief	:	An object
 * @author	:	Fredrik "quarn" Ehnbom <quarn@home.se>
 *
 */

#include "Matrix.h"
#include "Point3D.h"

namespace q3d {

class Object {
protected:
	Point3D pos;		// object Position;
	char*	name;		// Name of object
	Matrix matrix;		// Objects matrix

	bool updateMatrix;	// wheter or not an update of the matrix is needed
	bool lastFrameUpdated;	// wheter or not this object was updated the last frame

public:
	Object();
	virtual ~Object();

	void update();
	void setName(char *name);
	const char* getName();

	Matrix *getMatrix();

	// force an update of the matrix
	void forceUpdate();
	void setPosition(const Point3D&);
	const Point3D& getPosition();

	const bool wasUpdated();
};

}
#endif
