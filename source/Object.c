#include <q3d/Object.h>

namespace q3d {

Object::Object() {
	name = NULL;

	updateMatrix = true;
	lastFrameUpdated = false;
}

Object::~Object() {
	if (name != NULL) delete[] name;
	name = NULL;
}

void Object::setName(char *name) {
	this->name = name;
}

const char *Object::getName() {
	return name;
}

void Object::setPosition(const Point3D &p) {
	if (pos == p) return;
	pos = p;
	updateMatrix = true;
}

void Object::forceUpdate() {
	updateMatrix = true;
}

const Point3D &Object::getPosition() {
	return pos;
}

Matrix *Object::getMatrix() {
	// since the user requests the matrix manually,
	// the matrix probably will be updated
	updateMatrix = true;
	return &matrix;
}

const bool Object::wasUpdated() {
	if (lastFrameUpdated) {
		lastFrameUpdated = false;
		return true;
	}
	return false;
}
}
