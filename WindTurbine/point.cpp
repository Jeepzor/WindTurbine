#include "point.h"

namespace wind {
	Point::Point(double xPos, double yPos) {
		x = xPos;
		y = yPos;
	}
	
	Point::Point() {
		x = 0;
		y = 0;
	}
}