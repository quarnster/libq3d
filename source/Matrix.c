#include <kos.h>
#include <assert.h>
#include "Matrix.h"

#define MATRIX_STACK_SIZE 8

unsigned int _q3dMatrixStackPos = 0;
static q3dTypeMatrix _q3dMatrixStack[MATRIX_STACK_SIZE] __attribute__((aligned(32)));

q3dTypeMatrix _q3dMatrixObject __attribute__((aligned(32)));
q3dTypeMatrix _q3dMatrixCamera __attribute__((aligned(32)));
q3dTypeMatrix _q3dMatrixTemp __attribute__((aligned(32)));
q3dTypeMatrix _q3dMatrixPerspective __attribute__((aligned(32))) = {
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f }
};

#define XCENTER 320.0f
#define YCENTER 240.0f

// Screen view matrix (used to transform to screen space) 
matrix_t screenview_matrix __attribute__((aligned(32))) = {
	{ YCENTER,    0.0f,   0.0f,  0.0f },
	{    0.0f, YCENTER,   0.0f,  0.0f },
	{    0.0f,    0.0f,   1.0f,  0.0f },
	{ XCENTER, YCENTER,   0.0f,  1.0f }
};

// Projection matrix (does perspective)
/*
matrix_t projection_matrix = {
	{ 1.0f,       0.0f,                      0.0f,  0.0f },
	{       0.0f, 1.0f,                      0.0f,  0.0f },
	{       0.0f,       0.0f, 1.0f, 1.0f },
	{       0.0f,       0.0f, 0.0f,  1.0f }
};
*/

#define ZNEAR		1.0f
#define ZFAR		100.0f

#define COT_FOVY_2	1.0f /* 90 degree view angle */

q3dTypeMatrix projection_matrix __attribute__((aligned(32))) = {
	{ COT_FOVY_2,       0.0f,                      0.0f,  0.0f },
	{       0.0f, COT_FOVY_2,                      0.0f,  0.0f },
	{       0.0f,       0.0f, (ZFAR+ZNEAR)/(ZNEAR-ZFAR), -1.0f },
	{       0.0f,       0.0f, 2*ZFAR*ZNEAR/(ZNEAR-ZFAR),  1.0f }
};

void q3dMatrixInit() {
	//q3dMatrixIdentity();
	q3dMatrixLoad(&screenview_matrix);
	q3dMatrixApply(&projection_matrix);
	q3dMatrixStore(&_q3dMatrixPerspective);
}

void q3dMatrixPush() {
	q3dMatrixStore(&_q3dMatrixTemp);

	assert_msg(_q3dMatrixStackPos < MATRIX_STACK_SIZE, "push over the cliff... ;)");
	memcpy(_q3dMatrixStack + _q3dMatrixStackPos, _q3dMatrixTemp, sizeof(q3dTypeMatrix));
	_q3dMatrixStackPos++;
}
void q3dMatrixPop() {
	_q3dMatrixStackPos--;

	assert_msg(_q3dMatrixStackPos > 0, "nothing to pop...");
	memcpy(_q3dMatrixTemp, _q3dMatrixStack + _q3dMatrixStackPos, sizeof(q3dTypeMatrix));
	q3dMatrixLoad(&_q3dMatrixTemp);
}

static q3dTypeMatrix mt __attribute__((aligned(32))) = {
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f }
};

void q3dMatrixTranslate(float x, float y, float z) {
	mt[3][0] = x;
	mt[3][1] = y;
	mt[3][2] = z;
	q3dMatrixApply(&mt);
}

static q3dTypeMatrix mx __attribute__((aligned(32))) = {
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f }
};

void q3dMatrixRotateX(float agl) {
	float c, s;

	// Rotation about X axis
	c = fcos(agl);
	s = fsin(agl);
	mx[1][1] = c;
	mx[1][2] =-s;
	mx[2][1] = s;
	mx[2][2] = c;

	q3dMatrixApply(&mx);
}

static q3dTypeMatrix my __attribute__((aligned(32))) = {
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f }
};
void q3dMatrixRotateY(float agl) {
	float c, s;

	// Rotation about Y axis
	c = fcos(agl);
	s = fsin(agl);
	my[0][0] = c;
	my[0][2] = s;
	my[2][0] =-s;
	my[2][2] = c;
	q3dMatrixApply(&my);
}

static q3dTypeMatrix mz __attribute__((aligned(32))) = {
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f }
};
void q3dMatrixRotateZ(float agl) {
	float c, s;

	// Rotation about Z axis
	c = fcos(agl);
	s = fsin(agl);
	mz[0][0] = c;
	mz[0][1] =-s;
	mz[1][0] = s;
	mz[1][1] = c;
	q3dMatrixApply(&mz);
}

static q3dTypeMatrix mxyz __attribute__((aligned(32))) = {
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f }

};

void q3dMatrixRotateXYZ(float x, float y, float z) {
	float c1, s1, c2, s2, c3, s3;

	c1 = fcos(x);
	s1 = fsin(x);
	c2 = fcos(y);
	s2 = fsin(y);
	c3 = fcos(z);
	s3 = fsin(z);

	mxyz[0][0] = c1*c3 + s1*s2*s3;
	mxyz[0][1] = -c1*s3 + c3*s1*s2;
	mxyz[0][2] = c2*s1;
	mxyz[1][0] = c2*s3;
	mxyz[1][1] = c2*c3;
	mxyz[1][2] = -s2;
	mxyz[2][0] = -c3*s1 + c1*s2*s3;
	mxyz[2][1] = s1*s3 + c1*c3*s2;
	mxyz[2][2] = c1 * c2;

	q3dMatrixApply(&mxyz);
/*
Ú                                                       ¿
³  c1c3 + s1s2s3        -c1s3 + c3s1s2          c2s1    ³
³                                                       ³
³      c2s3                  c2c3               -s2     ³
³                                                       ³
³ -c3s1 + c1s2s3         s1s3 + c1c3s2          c1c2    ³
À                                                       Ù
*/
}


static q3dTypeMatrix ms __attribute__((aligned(32))) = {
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f }
};

void q3dMatrixScale(float x, float y, float z) {
	ms[0][0] = x;
	ms[1][1] = y;
	ms[2][2] = z;
	q3dMatrixApply(&ms);
}

void q3dMatrixTransformNormals(q3dTypeVector *source, q3dTypeVector *target, int length) {
	int i;
	float x, y, z;

//	q3dMatrixStore(&_q3dMatrixTemp);

	for (i = 0; i < length; i++) {
		x = source[i].x;
		y = source[i].y;
		z = source[i].z;

		target[i].x = x * _q3dMatrixTemp[0][0] + y * _q3dMatrixTemp[1][0] + z * _q3dMatrixTemp[2][0];
		target[i].y = x * _q3dMatrixTemp[0][1] + y * _q3dMatrixTemp[1][1] + z * _q3dMatrixTemp[2][1];
		target[i].z = x * _q3dMatrixTemp[0][2] + y * _q3dMatrixTemp[1][2] + z * _q3dMatrixTemp[2][2];

	}

}
