#ifndef __INCLUDED_Q3D_CAMERA_H
#define __INCLUDED_Q3D_CAMERA_H

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3d-engine ;) (c) Outbreak 2001-2002        =
 * ===========================================================================
 *
 *
 * @id		:	$Id: Camera.h,v 1.1 2004/01/24 21:41:43 quarn Exp $
 * @brief	:	Camera
 * @author	:	Fredrik Ehnbom
 *
 */

// #include "Polyhedron.h"
#include "Vertex.h"
#include "Angle.h"

typedef struct {
	// private members
	float		_roll;		// Roll angle
	q3dTypeAngle	_agl;		// Rotation angle
	q3dTypeVertex	_pos;		// Position

	uint8		_updateMatrix;	// wheter or not the matrix should be updated
} q3dTypeCamera;

void q3dCameraInit(q3dTypeCamera *cam);
void q3dCameraFree(q3dTypeCamera *cam);
// void q3dCameraPerspective(float angle, float znear, float zfar);
void q3dCameraUpdate(q3dTypeCamera *cam);
// void q3dCameraProject(q3dTypeCamera *cam, q3dTypePolyhedron *poly);
void q3dCameraSetRotation(q3dTypeCamera *cam, q3dTypeAngle *agl);
void q3dCameraSetPosition(q3dTypeCamera *cam, q3dTypeVertex *pos);

#endif
