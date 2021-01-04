#include "math.h"

namespace wind {

	double Math::distance(double x1, int y1, double x2, double y2) const {
		double dx = x1 - x2;
		double dy = y1 - y2;
		return std::sqrt(dx * dx + dy * dy);
	}

	// LINE/POINT
	bool Math::linePoint(double x1, double y1, double x2, double y2, double px, double py) {

		// get distance from the point to the two ends of the line
		double d1 = distance(px, py, x1, y1);
		double d2 = distance(px, py, x2, y2);

		// get the length of the line
		double lineLen = distance(x1, y1, x2, y2);

		// since floats are so minutely accurate, add
		// a little buffer zone that will give collision
		double buffer = 1;    // higher # = less accurate

		// if the two distances are equal to the line's
		// length, the point is on the line!
		// note we use the buffer here to give a range,
		// rather than one #
		if (d1 + d2 >= lineLen - buffer && d1 + d2 <= lineLen + buffer) {
			return true;
		}
		return false;
	}

	Math math;
}