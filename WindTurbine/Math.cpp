#include "math.h"

namespace wind {

	double Math::distance(double x1, int y1, double x2, double y2) const {
		double dx = x1 - x2;
		double dy = y1 - y2;
		return std::sqrt(dx * dx + dy * dy);
	}

	// LINE/POINT
	bool Math::pointInLine(double x1, double y1, double x2, double y2, double px, double py) {
		double v1_distance = distance(px, py, x1, y1); // Distance from vector 1 to point
		double v2_distance = distance(px, py, x2, y2); // Distance from vector 2 to point
		double line_length = distance(x1, y1, x2, y2); // Distance from vector 1 to vector 2
		double buffer = 1; //Higher buffer = safer, but less accurate.   

		if (v1_distance + v2_distance >= line_length - buffer && v1_distance + v2_distance <= line_length + buffer) {
			return true;
		}
		return false;
	}

	Math math;
}