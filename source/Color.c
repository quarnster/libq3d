#include "Color.h"

void q3dColorSetV(q3dTypeColor *dest, q3dTypeColor *source) {
	dest->a = source->a;
	dest->r = source->r;
	dest->g = source->g;
	dest->b = source->b;
}

void q3dColorSet3f(q3dTypeColor *c, float r, float g, float b) {
	c->r = r;
	c->g = g;
	c->b = b;
}

void q3dColorSet4f(q3dTypeColor *c, float r, float g, float b, float a) {
	c->r = r;
	c->g = g;
	c->b = b;
	c->a = a;
}
