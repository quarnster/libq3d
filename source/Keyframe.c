#include <q3d/KeyFrame.h>

namespace q3d {

KeyFrame::KeyFrame() : Point3D() {
	tension = continuity = bias = time = 0;
}
}
