#ifndef __INCLUDED_Q3D_MATRIX_H
#define __INCLUDED_Q3D_MATRIX_H

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3d-engine ;) (c) Outbreak 2001-2002        =
 * ===========================================================================
 *
 * @id		:	$Id: Matrix.h,v 1.2 2004/01/28 20:14:02 quarn Exp $
 * @brief	:	Matrix code
 * @author	:	Fredrik "quarn" Ehnbom <quarn@home.se>
 *
 */
#include <kos.h>

#include "Vertex.h"
#include "Vector.h"
/*
#include "Point3D.h"

namespace q3d {
class Matrix {
public:
	float data[4][4];

	Matrix();
	void identity();

	void rotateX(float agl);
	void rotateY(float agl);
	void rotateZ(float agl);

	void translate(float x, float y, float z);

	void load(Matrix*);
	void store(Matrix*);

	void apply(Matrix*);

	void transformNormals(Point3D *source, Point3D *target, int off, int length);
	void transform(Point3D *source, Point3D *target, int off, int length);

	void transformNormals(Point3D *source, Point3D *target, int length);
	void transform(Point3D *source, Point3D *target, int length);
	void transform(Point3D *source, pvr_vertex_t *target, int length);
};
}
*/

typedef float q3dTypeMatrix[4][4];

extern q3dTypeMatrix _q3dMatrixObject __attribute__((aligned(32)));
extern q3dTypeMatrix _q3dMatrixPerspective __attribute__((aligned(32)));
extern q3dTypeMatrix _q3dMatrixTemp __attribute__((aligned(32)));
extern q3dTypeMatrix _q3dMatrixCamera __attribute__((aligned(32)));

#define q3dMatrixIdentity	mat_identity
#define q3dMatrixLoad(a)	mat_load(a)
#define q3dMatrixStore(a)	mat_store(a)
#define q3dMatrixApply(a)	mat_apply(a)

// loads the identity matrix into the internal matrix
//void q3dMatrixIdentity();

// Initialize the screen and perspective matrices
void q3dMatrixInit();

// applies a matrix for rotation in x "agl"-degrees
void q3dMatrixRotateX(float agl);
// applies a matrix for rotation in y "agl"-degrees
void q3dMatrixRotateY(float agl);
// applies a matrix for rotation in z "agl"-degrees
void q3dMatrixRotateZ(float agl);
// applies a matrix for rotation in xyz
void q3dMatrixRotateXYZ(float aglx, float agly, float aglz);
// applies a translation matrix
void q3dMatrixTranslate(float x, float y, float z);
// applies a scale matrix
void q3dMatrixScale(float x, float y, float z);

// pushes the internal matrix (can be done 4 times)
void q3dMatrixPush();
// pops the internal matrix
void q3dMatrixPop();

// loads the specified onto the internal matrix
void q3dMatrixLoad(q3dTypeMatrix *matrix);
// stores the internal matrix into the specified matrix
void q3dMatrixStore(q3dTypeMatrix *matrix);
// applies (mul) the specified matrix with the internal
void q3dMatrixApply(q3dTypeMatrix *matrix);

void q3dMatrixTransform(q3dTypeVertex *source, void *target, int length, int destPitch);
void q3dMatrixTransformNormals(q3dTypeVector *source, q3dTypeVector *target, int length);

/*
// transform normals (rotate only)
void q3d_Matrix_transformNormals(q3d_Point *source, q3d_Point *target, int length);
// transform
void q3d_Matrix_transform(q3d_Point *source, q3d_Point *target, int length);
*/
/*
typedef float q3d_Matrix[4][4];

extern q3d_Matrix _q3d_internal_matrix;

// loads the identity matrix into the internal matrix
void q3d_Matrix_identity();

// applies a matrix for rotation in x "agl"-degrees
void q3d_Matrix_rotateX(float agl);
// applies a matrix for rotation in y "agl"-degrees
void q3d_Matrix_rotateY(float agl);
// applies a matrix for rotation in z "agl"-degrees
void q3d_Matrix_rotateZ(float agl);
// applies a translation matrix
void q3d_Matrix_translate(float x, float y, float z);

// pushes the internal matrix (can be done 4 times)
void q3d_Matrix_push();
// pops the internal matrix
void q3d_Matrix_pop();

// loads the specified onto the internal matrix
void q3d_Matrix_load(q3d_Matrix *matrix);
// stores the internal matrix into the specified matrix
void q3d_Matrix_store(q3d_Matrix *matrix);
// applies (mul) the specified matrix with the internal
void q3d_Matrix_apply(q3d_Matrix *matrix);

// transform normals (rotate only)
void q3d_Matrix_transformNormals(q3d_Point *source, q3d_Point *target, int length);
// transform
void q3d_Matrix_transform(q3d_Point *source, q3d_Point *target, int length);
*/
#endif
