// #include <kos.h>
#include "Vertex.h"

int q3dVertexEquals(q3dTypeVertex *v, q3dTypeVertex *v2) {
	return (v->x == v2->x) && (v->y == v2->y) && (v->z == v2->z);
}

void q3dVertexSetV(q3dTypeVertex *v, q3dTypeVertex *v2) {
	v->x = v2->x;
	v->y = v2->y;
	v->z = v2->z;
}

void q3dVertexInit(q3dTypeVertex *v) {
	v->x = v->y = v->z = 0;
}

void q3dVertexSet3f(q3dTypeVertex *v, float x, float y, float z) {
	v->x = x;
	v->y = y;
	v->z = z;
}

/*
void Point3D::set(float x2, float y2, float z2) {
	x = x2;
	y = y2;
	z = z2;
}

void Point3D::cross(const Point3D &p1, const Point3D &p2) {
	x = p1.y*p2.z - p1.z*p2.y;
	y = p1.z*p2.x - p1.x*p2.z;
	z = p1.x*p2.y - p1.y*p2.x;
}

void Point3D::normalize() {
	float len = fsqrt(x*x+y*y+z*z);
	x /= len;
	y /= len;
	z /= len;
}

void Point3D::operator=(const Point3D &p) {
	x = p.x;
	y = p.y;
	z = p.z;
}

Point3D Point3D::operator+(const Point3D &p) {
	Point3D tmp = *this;
	tmp.x += p.x;
	tmp.y += p.y;
	tmp.z += p.z;

	return tmp;
}

Point3D Point3D::operator*(const float &p) {
	Point3D tmp = *this;
	tmp.x *= p;
	tmp.y *= p;
	tmp.z *= p;

	return tmp;
}

Point3D Point3D::operator-(const Point3D &p) {
	Point3D tmp = *this;
	tmp.x -= p.x;
	tmp.y -= p.y;
	tmp.z -= p.z;

	return tmp;
}
Point3D Point3D::operator+=(const Point3D& p) {
	*this = *this + p;
	return *this;
}
Point3D Point3D::operator-=(const Point3D& p) {
	*this = *this - p;
	return *this;
}

bool Point3D::operator==(const Point3D &p) const{
	return (x == p.x) && (y == p.y) && (z == p.z);
}
*/
