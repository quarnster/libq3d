TARGET = libq3d.a
OBJS = \
	Camera.o \
	Color.o \
	Material.o \
	Matrix.o \
	Matrix_asm.o \
	Texel.o \
	Angle.o \
	Vector.o \
	Vertex.o \
	Polygon.o \
	Polyhedron.o \
	Texture.o \
	Filler.o \
	FillerCell.o \
	FillerTexture.o \
	FillerEnvironment.o \
	FillerWireframe.o \
	FillerStandard.o


include $(KOS_BASE)/addons/Makefile.prefab

KOS_CFLAGS += -I../include

clean:
	rm -f *~ *.o *.a
