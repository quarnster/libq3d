#ifndef __INCLUDED_Q3D_3DS_H
#define __INCLUDED_Q3D_3DS_H

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3d-engine ;) (c) Outbreak 2001-2002        =
 * ===========================================================================
 *
 * @id		:	$Id: Load3DS.h,v 1.1 2004/01/24 21:41:43 quarn Exp $
 * @brief	:	.3ds loader
 * @author	:	Fredrik Ehnbom
 *
 */
#include <vector>
#include <kos.h>
#include "Polyhedron.h"
#include "Camera.h"
#include "Material.h"
#include <utils/Memfile.h>

#define	MESH		0
#define	CAMERA		1
#define CAMERA_TARGET	2

namespace q3d {

class tmpMaterial {
public:
	char *name;
	uint32 diffuse;

	tmpMaterial() {
		name = new char[256];
	}
	~tmpMaterial() {
		delete[] name;
	}
};

class Load3DS {
private:
	std::vector<tmpMaterial*> material;

	int mode;
	int keyFrameStart;
	int keyFrameLength;
	char tmpName[20];

	uint32 getInt32(Memfile *memfile);
	uint16 getInt16(Memfile *memfile);
	float getFloat32(Memfile *memfile);
	void parse(Memfile *memfile);

public:
	std::vector<Polyhedron*> object;
	std::vector<Camera*> camera;

	~Load3DS();
	void load(char *name);
};

}

#endif
