#include "math.h"

namespace wind {

	double Math::distance(double x1, int y1, double x2, double y2) const {
		double dx = x1 - x2;
		double dy = y1 - y2;
		return std::sqrt(dx * dx + dy * dy);
	}

	Math math;
}