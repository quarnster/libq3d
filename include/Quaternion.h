#ifndef __INCLUDE_Q3D_QUATERNION_H
#define __INCLUDE_Q3D_QUATERNION_H

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3d-engine ;) (c) Outbreak 2001-2004        =
 * ===========================================================================
 *
 * @id		:	$Id: Quaternion.h,v 1.1 2004/03/18 09:52:06 quarn Exp $
 * @brief	:	A quaternion representation
 * @author	:	Fredrik Ehnbom
 *
 */

#include "Matrix.h"
#include "Vector.h"

typedef struct {
	float w;
	float x;
	float y;
	float z;
} q3dTypeQuaternion;


inline void q3dQuaternionSetV(q3dTypeQuaternion *v, q3dTypeQuaternion *v2) {
	v->w = v2->w;
	v->x = v2->x;
	v->y = v2->y;
	v->z = v2->z;
}

inline void q3dQuaternionSet4f(q3dTypeQuaternion *v, float w, float x, float y, float z) {
	v->w = w;
	v->x = x;
	v->y = y;
	v->z = z;
}

inline void q3dQuaternionInit(q3dTypeQuaternion *v) {
	v->x = v->y = v->z = 0;
	v->w = 1;
}

inline void q3dQuaternionNormalize(q3dTypeQuaternion *q) {
	float fr = frsqrt(q->w * q->w + q->x * q->x + q->y * q->y + q->z * q->z);
	q->w *= fr;
	q->x *= fr;
	q->y *= fr;
	q->z *= fr;
}

inline void q3dQuaternionMul(q3dTypeQuaternion *q1, q3dTypeQuaternion *q2) {
	float w = q1->w * q2->w - q1->x * q2->x - q1->y * q2->y - q1->z * q2->z;
	float x = q1->w * q2->x + q1->x * q2->w + q1->y * q2->z - q1->z * q2->y;
	float y = q1->w * q2->y + q1->y * q2->w + q1->z * q2->x - q1->x * q2->z;
	float z = q1->w * q2->z + q1->z * q2->w + q1->x * q2->y - q1->y * q2->x;

	q1->w = w;
	q1->x = x;
	q1->y = y;
	q1->z = z;
}

// v = v + v2;
inline void q3dQuaternionAdd(q3dTypeQuaternion *v, q3dTypeQuaternion *v2) {
	v->w += v2->w;
	v->x += v2->x;
	v->y += v2->y;
	v->z += v2->z;
}

inline void q3dQuaternionFromVectorTheta(q3dTypeQuaternion *q, q3dTypeVector *v, float theta) {
	// initializes a quaternion based on a 3d-direction vector and angle
	// note the direction vector must be a unit vector
	// and the angle is in rads
	float theta_div_2 = (0.5) * theta;

	// compute the quaternion, note this is from chapter 4
	// pre-compute to save time
	float sin_theta = fsin(theta_div_2);

	q->x = sin_theta * v->x;
	q->x = sin_theta * v->y;
	q->x = sin_theta * v->z;
	q->w = fcos(theta_div_2);
}

//
inline void q3dQuaternionToMatrix(q3dTypeQuaternion *q) {
	float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

	// calculate coefficients
	x2 = q->x + q->x;
	y2 = q->y + q->y;
	z2 = q->z + q->z;

	xx = q->x * x2; xy = q->x * y2; xz = q->x * z2;
	yy = q->y * y2; yz = q->y * z2; zz = q->z * z2;
	wx = q->w * x2; wy = q->w * y2; wz = q->w * z2;

	_q3dMatrixTemp[0][0] = 1.0f - (yy + zz);
	_q3dMatrixTemp[0][1] = xy - wz;
	_q3dMatrixTemp[0][2] = xz + wy;
	_q3dMatrixTemp[0][3] = 0.0;

	_q3dMatrixTemp[1][0] = xy + wz;
	_q3dMatrixTemp[1][1] = 1.0f - (xx + zz);
	_q3dMatrixTemp[1][2] = yz - wx;
	_q3dMatrixTemp[1][3] = 0;

	_q3dMatrixTemp[2][0] = xz - wy;
	_q3dMatrixTemp[2][1] = yz + wx;
	_q3dMatrixTemp[2][2] = 1.0f - (xx + yy);
	_q3dMatrixTemp[2][3] = 0;

	_q3dMatrixTemp[3][0] = 0;
	_q3dMatrixTemp[3][1] = 0;
	_q3dMatrixTemp[3][2] = 0;
	_q3dMatrixTemp[3][3] = 1;

}

#endif
