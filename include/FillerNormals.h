#ifndef __INCLUDED_Q3D_NORMALFILLER_H
#define __INCLUDED_Q3D_NORMALFILLER_H

/**
 * ===========================================================================
 * = Q3D - quarns quick and dirty 3D-engine ;) (c) Outbreak 2001-2002        =
 * ===========================================================================
 *
 * @id		:	$Id: FillerNormals.h,v 1.1 2004/01/24 21:41:43 quarn Exp $
 * @brief	:	A filler which draws the normals
 * @author	:	Fredrik "quarn" Ehnbom <quarn@home.se>
 *
 */
#include "Filler.h"

namespace q3d {

class NormalFiller : public Filler{
private:
	pvr_poly_hdr_t lineHdr;

	void drawLine(Point3D *p1, Point3D *p2, float thickness);

public:
	NormalFiller();

	void update(Polyhedron *poly);
	void draw(Polyhedron *polyhedron);
};

}

#endif

