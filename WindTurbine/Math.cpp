#include "math.h"

namespace wind {

	Math::Math() {
		std::srand(static_cast<unsigned int>(time(0)));
	}
	double Math::distance(double x1, double y1, double x2, double y2) const { //return distance between two points
		double dx = x1 - x2;
		double dy = y1 - y2;
		return std::sqrt(dx * dx + dy * dy);
	}
	
	double Math::getAngle(double x1, double y1, double x2, double y2) const { // return angle between two points
		double dx = x1 - x2;
		double dy = y1 - y2;
		return atan2(y2 - y1, x2 - x1);
	}	
	
	double Math::clamp(double min, double max, double value) const { // Return clamped value in a set range.
		return (value < min) ? min : (value > max) ? max : value;
	}

	// Return true if point is on the line
	bool Math::pointInLine(double x1, double y1, double x2, double y2, double px, double py) { 
		double v1_distance = distance(px, py, x1, y1); // Distance from line 1 to point
		double v2_distance = distance(px, py, x2, y2); // Distance from line 2 to point
		double line_length = distance(x1, y1, x2, y2); // Distance from line 1 to line 2
		double buffer = 1; //Higher buffer = safer, but less accurate.   

		if (v1_distance + v2_distance >= line_length - buffer && v1_distance + v2_distance <= line_length + buffer) {
			return true;
		}
		return false;
	}

	double Math::random() const{
		return (double)std::rand() / (double)RAND_MAX;
	}

	Math math;
}