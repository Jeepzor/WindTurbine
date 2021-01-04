#ifndef MATH_H
#define MATH_H

#include <iostream>
#include <string>

namespace wind {
	struct Math {

		double distance(double x, int y, double x2, double y2) const;
		bool pointInLine(double x1, double y1, double x2, double y2, double px, double py);
		
	};

	extern Math math;
}

#endif