#include <kos.h>
#include <utils/Memfile.h>
#include <q3d/Load3DS.h>
#include <q3d/KeyFramer.h>


void _printName(uint32 chunk) {
	static char *table = "0123456789ABCDEF";

	printf(
		"%c%c%c%c\n",
		table[(chunk>>12)&0x0f],
		table[(chunk>>8)&0x0f],
		table[(chunk>>4)&0x0f],
		table[(chunk>>0)&0x0f]
	);
}
namespace q3d {

uint16 Load3DS::getInt16(Memfile *memfile) {
	return (memfile->getc()) + (memfile->getc()<< 8);
}

uint32 Load3DS::getInt32(Memfile *memfile) {
	return (memfile->getc()) + (memfile->getc()<< 8) + (memfile->getc() << 16) + (memfile->getc() << 24);
}
float Load3DS::getFloat32(Memfile *memfile) {
	union {
		float f;
		uint32 i;
	} _floatConv;

	_floatConv.i = getInt32(memfile);
	return _floatConv.f;
}

void Load3DS::parse(Memfile *memfile) {
//	printf("file pos: %d\n", memfile->_pos);

	uint32 chunk = getInt16(memfile);
	uint32 length = getInt32(memfile);
	length -= 6;

//	_printName(chunk);
//	_printTag(chunk, length);

	switch (chunk) {
		default:
			memfile->seek(length, SEEK_CUR);
			break;
		case 0x4d4d: // 3ds file...
			break;
		case 0x3d3d: // 3d editor chunk
			break;
		case 0x4000: // objectblock (with name)
		{
			memset(tmpName, '\0', 20);
			int i = 0;
			while ((tmpName[i++] = memfile->getc()) != 0);

			printf("name: %s\n", tmpName);
//			char c;
//			int i = 0;
//			while ((c = memfile->getc()) != 0) {
//				printf("%c", c);
//				i++;
//			}
//			printf("\n");
//			printf("\ni: %d\n", i);
//			activePolyhedron = "";
//			while (buffer[index++] != 0) activePolyhedron += (char) buffer[index-1];
			break;
		}

		case 0x4100: // Triangular mesh
		{
			Polyhedron *p = new Polyhedron();
			object.push_back(p);
			char *name = new char[strlen(tmpName)+1];
			strncpy(name, tmpName, strlen(tmpName)+1);
			p->setName(name);

			break;
		}
		case 0x4110: // vertex list
		{
			Polyhedron *p = (Polyhedron *) object.back();

			// create vertices
			p->vertexLength = getInt16(memfile);
			p->vertex = new Point3D[p->vertexLength];

			int i;
			for (i = 0; i < p->vertexLength; i++) {
				p->vertex[i].x = getFloat32(memfile) * 0.01;
				p->vertex[i].z = getFloat32(memfile) * 0.01;
				p->vertex[i].y = -getFloat32(memfile) * 0.01;
			}
			break;
		}
		case 0x4120: // face info
		{
			Polyhedron *p = (Polyhedron *) object.back();

			p->polygonLength = getInt16(memfile);
			p->polygon = new Polygon[p->polygonLength];

			for (int i = 0; i < p->polygonLength; i++) {
				p->polygon[i].vertexLength = 3;
				p->polygon[i].vertex = new uint16[3];
				p->polygon[i].texCoord = NULL;
				

				p->polygon[i].vertex[0] = getInt16(memfile);
				p->polygon[i].vertex[2] = getInt16(memfile);
				p->polygon[i].vertex[1] = getInt16(memfile);

				// visible shit...
				memfile->seek(2, SEEK_CUR);
			}
			break;
		}
		case 0x4130: // Faces material list
		{
			Polyhedron *p = (Polyhedron *) object.back();
			char *temp = new char[256];
			memset(temp, '\0', 256);
			tmpMaterial *mat = NULL;

			int j = 0;
			while ((temp[j++] = memfile->getc()) != 0);

			int entries = getInt16(memfile);

			for (unsigned int i = 0; i < material.size(); i++) {
				mat = material[i];
				if (!strcmp(mat->name, temp)) {
					break;
				}
			}
			delete[] temp;

			memfile->seek(2*entries, SEEK_CUR);

			if (mat == NULL) {
				printf("MATERIAL NOT FOUND!\n");
				break;
			}

			p->material.color.a = ((mat->diffuse >> 24) & 0xff) / 255.0f;
			p->material.color.r = ((mat->diffuse >> 16) & 0xff) / 255.0f;
			p->material.color.g = ((mat->diffuse >>  8) & 0xff) / 255.0f;
			p->material.color.b = ((mat->diffuse >>  0) & 0xff) / 255.0f;

			break;
		}

		case 0x4160: // Local coordinate system
		{
			Polyhedron *p = (Polyhedron *) object.back();
			Matrix mat;
/*
			// read matrix
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					mat.data[i][j] = getFloat32(memfile);

			for (int i = 0; i < 3; i++)
				std::swap(mat.data[i][1], mat.data[i][2]);
			for (int j = 0; j < 3; j++)
				std::swap(mat.data[1][j], mat.data[2][j]);
*/
//			mat.data[0][1] = - mat.data[0][1];
//			mat.data[1][1] = - mat.data[1][1];
//			mat.data[2][1] = - mat.data[2][1];

//			mat.data[1][0] = - mat.data[1][0];
//			mat.data[1][2] = - mat.data[1][2];
			memfile->seek(4 * 3 * 3, SEEK_CUR);

			Point3D tmp;
			tmp.x = getFloat32(memfile) * 0.01;
			tmp.z = getFloat32(memfile) * 0.01;
			tmp.y = -getFloat32(memfile) * 0.01;

//			p->setPosition(tmp);
//			for (int i = 0; i < p->vertexLength; i++) {
//				p->vertex[i] -= tmp;
//			}
//			mat.transformNormals(p->vertex, p->vertex, 0, p->vertexLength);
//			p->origin.set(0, 0, 0);
			break;
		}
		case 0x4700: // camera
		{
			Camera *c = new Camera();
			camera.push_back(c);
			char *name = new char[strlen(tmpName)+1];
			strncpy(name, tmpName, strlen(tmpName)+1);
			c->setName(name);

			Point3D tmp;
			tmp.x = getFloat32(memfile) * 0.01;
			tmp.z = getFloat32(memfile) * 0.01;
			tmp.y = -getFloat32(memfile) * 0.01;
			c->setPosition(tmp);

			tmp.x = getFloat32(memfile) * 0.01;
			tmp.z = getFloat32(memfile) * 0.01;
			tmp.y = -getFloat32(memfile) * 0.01;
			c->setTarget(tmp);

			// bank and lens
			memfile->seek(2*4, SEEK_CUR);
			break;
		}
		case 0xAFFF: // material chunk
			break;
		case 0xA000: // material name
		{
			char *temp = new char[256];

			int i = 0;
			while ((temp[i++] = memfile->getc()) != 0);

			tmpMaterial *mat = new tmpMaterial();
			strncpy(mat->name, temp, i);

			material.push_back(mat);

			delete[] temp;

			break;
		}
		case 0xA020: // material diffuse color
		{
			tmpMaterial *mat = (tmpMaterial *) material.back();
			memfile->seek(6, SEEK_CUR);

			mat->diffuse = 0xff000000 | memfile->getc() << 16;
			mat->diffuse |= memfile->getc() << 8;
			mat->diffuse |= memfile->getc();
			break;
		}
		case 0xB000: // keyframe
			break;
		case 0xB002: // Mesh information block
			mode = MESH;
			break;
		case 0xB003: // Camera information block
			mode = CAMERA;
			break;
		case 0xB004: // Camera target information block
			mode = CAMERA_TARGET;
			break;
		case 0xB008: // Frames (start and end)
			keyFrameStart	= getInt32(memfile);
			keyFrameLength	= getInt32(memfile);
			break;
		case 0xB010: // Object name, parameters and hierarchy father
		{
			memset(tmpName, '\0', 20);
			int i = 0;
			while ((tmpName[i++] = memfile->getc()) != 0);

			// flag1, flag2, father
			memfile->seek(6, SEEK_CUR);
//			index += 2; // flag1
//			index += 2; // flag2
//			index += 2; // father

			break;
		}
		case 0xB013: // Object pivot point
		{
			if (mode == MESH) {
				Polyhedron *p = NULL;
				for (unsigned int i = 0; i < object.size(); i++) {
					p = object[i];
					if (!strcmp(p->getName(), tmpName)) {
						break;
					}
				}
				if (p == NULL) {
					memfile->seek(length, SEEK_CUR);
					break;
				}
				p->pivot.x = getFloat32(memfile) * 0.01;
				p->pivot.z = getFloat32(memfile) * 0.01;
				p->pivot.y = -getFloat32(memfile) * 0.01;
				printf("%fd, %fd, %fd\n", p->pivot.x, p->pivot.y, p->pivot.z);

				for (int i = 0; i < p->vertexLength; i++) {
					p->vertex[i] -= p->pivot;
				}

			} else {
				memfile->seek(length, SEEK_CUR);
			}
			break;
		}
		case 0xB020: // Position track
		{
			memfile->seek(2, SEEK_CUR); // Flag
			memfile->seek(8, SEEK_CUR); // unknown
			uint32 length = getInt32(memfile);

			KeyFrame *keyFrame = new KeyFrame[length];

			for (uint32 i = 0; i < length; i++) {
				uint32 which = getInt32(memfile);
				uint16 data = getInt16(memfile);

				if ((data & 0x1) > 0) keyFrame[i].tension = getFloat32(memfile);
				if ((data & 0x2) > 0) keyFrame[i].continuity = getFloat32(memfile);
				if ((data & 0x4) > 0) keyFrame[i].bias = getFloat32(memfile);
				if ((data & 0x8) > 0) memfile->seek(4, SEEK_CUR);; // Ease to
				if ((data & 0x10) > 0) memfile->seek(4, SEEK_CUR);; // Ease from

				keyFrame[i].x = getFloat32(memfile) * 0.01;
				keyFrame[i].z = getFloat32(memfile) * 0.01;
				keyFrame[i].y = -getFloat32(memfile) * 0.01;
				
				keyFrame[i].time = (which*34) / 1000.0f;
			}
			if (length > 1) {
				KeyFramer::generate(keyFrame, length);
			}

			if (mode == MESH) {
				Polyhedron *p = NULL;
				for (unsigned int i = 0; i < object.size(); i++) {
					p = object[i];
					if (!strcmp(p->getName(), tmpName)) {
						break;
					}
				}
				if (p == NULL || p->positionTrack != NULL) {
					delete[] keyFrame;
					break;
				}
				p->positionTrack = keyFrame;
				p->positionTrackLength = length;

			} else if (mode == CAMERA) {
				Camera *c = NULL;
				for (unsigned int i = 0; i < camera.size(); i++) {
					c = camera[i];
					if (!strcmp(c->getName(), tmpName)) {
						break;
					}
				}
				if (c == NULL || c->positionTrack != NULL) {
					delete[] keyFrame;
					break;
				}
				c->positionTrack = keyFrame;
				c->positionTrackLength = length;
			} else if (mode == CAMERA_TARGET) {
				Camera *c = NULL;
				for (unsigned int i = 0; i < camera.size(); i++) {
					c = camera[i];
					if (!strcmp(c->getName(), tmpName)) {
						break;
					}
				}
				if (c == NULL || c->targetTrack != NULL) {
					delete[] keyFrame;
					break;
				}
				c->targetTrack = keyFrame;
				c->targetTrackLength = length;
			} else {
				delete[] keyFrame;
			}
			break;
		}
	}

	while (memfile->available())
		parse(memfile);
}

Load3DS::~Load3DS() {
	for (uint32 i = 0; i < material.size(); i++) {
		delete material[i];
	}
	material.clear();

	for (uint32 i = 0; i < object.size(); i++) {
		delete object[i];
	}
	object.clear();

	for (uint32 i = 0; i < camera.size(); i++) {
		delete camera[i];
	}
	camera.clear();
}

void Load3DS::load(char *name) {
	Memfile memfile;

	if (!memfile.open(name)) {
		printf("Failed to open \"%s\"", name);
	}

	parse(&memfile);

	memfile.close();
}
}
