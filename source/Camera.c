#include <kos.h>
#include "Camera.h"
#include "Matrix.h"

void q3dCameraInit(q3dTypeCamera *cam) {
	cam->_roll = 0;
	q3dVertexInit(&cam->_pos);
	q3dAngleInit(&cam->_agl);
}
// void q3dCameraPerspective(float angle, float znear, float zfar);
void q3dCameraUpdate(q3dTypeCamera *cam) {
//	if (cam->_updateMatrix) {
		q3dMatrixIdentity();

		q3dMatrixTranslate( -cam->_pos.x, -cam->_pos.y, -cam->_pos.z);
		q3dMatrixRotateX(-cam->_agl.x);
		q3dMatrixRotateY(-cam->_agl.y);
		q3dMatrixRotateZ(-cam->_agl.z);

//		updateMatrix = false;
//		lastFrameUpdated = true;
//	} else {
//		lastFrameUpdated = false;
//	}
	q3dMatrixStore(&_q3dMatrixCamera);
}
/*
Camera::Camera(float angle, float znear, float zfar) : Object() {
	roll = 0;
	targetTrack = positionTrack = NULL;
	targetTrackLength = positionTrackLength = 0;
	perspective(angle, znear, zfar);
}
*/
/*
Camera::~Camera() {
	if (positionTrack != NULL) delete[] positionTrack;
	if (targetTrack != NULL) delete[] targetTrack;

	positionTrack = targetTrack = NULL;
	positionTrackLength = targetTrackLength = 0;
}
*/
/*
Matrix *Camera::getPerspectiveMatrix() {
	// since the user requests the matrix manually,
	// the matrix probably will be updated
	updateMatrix = true;
	return &pMatrix;
}
*/
/*
void Camera::project(Polyhedron *poly) {
	static Matrix tmp;

	// update vertices
	tmp.load(&pMatrix);
	tmp.apply(&matrix);
	tmp.apply(&poly->matrix);
	tmp.transform(poly->vertex, poly->finalVertex, poly->vertexLength);

	// update vertex normals
	tmp.load(&matrix);
	tmp.apply(&poly->matrix);

	tmp.transformNormals(poly->_polygonNormal, poly->pNormal, poly->polygonLength);
	tmp.transformNormals(poly->_vertexNormal, poly->vNormal, poly->vertexLength);
}
*/
/*
void Camera::perspective(float angle, float znear, float zfar) {
	float xc, yc;
	float cot_fovy_2;
	Matrix sm;
	Matrix pm;

	pMatrix.identity();

	// First, the screen matrix
	xc = vid_mode->width / 2.0f;
	yc = vid_mode->height / 2.0f;
	sm.data[0][0] = yc;
	sm.data[1][1] = yc;

	pMatrix.apply(&sm);

	// Second, the perspective projection matrix
	cot_fovy_2 = 1.0f / ftan(angle / 2);
	pm.data[0][0] = cot_fovy_2;
	pm.data[1][1] = cot_fovy_2;
	pm.data[2][2] = (zfar + znear) / (zfar - znear);

	pMatrix.apply(&pm);
}
*/
void q3dCameraSetRotation(q3dTypeCamera *cam, q3dTypeAngle *agl) {
	if (q3dAngleEquals(&cam->_agl, agl))
		return;
	q3dAngleSetV(&cam->_agl, agl);
	cam->_updateMatrix = true;
}
/*
void Camera::setTarget(const Point3D &p) {
	if (target == p) return;
	target = p;
	updateMatrix = true;
}
*/
void q3dCameraSetPosition(q3dTypeCamera *cam, q3dTypeVertex *pos) {
	if (q3dVertexEquals(&cam->_pos, pos)) return;
	q3dVertexSetV(&cam->_pos, pos);
//	cam->_pos = pos;
	cam->_updateMatrix = true;
}


