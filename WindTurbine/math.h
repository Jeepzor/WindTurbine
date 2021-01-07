#define PI 3.14159265

#ifndef MATH_H
#define MATH_H

#include <iostream>
#include <string>
namespace wind {
	struct Math {
		Math();
		double distance(double x, double y, double x2, double y2) const;
		double getAngle(double x, double y, double x2, double y2) const;
		double clamp(double min, double max, double value) const;
		double pi() { return PI; };
		double random() const;
		bool pointInLine(double x1, double y1, double x2, double y2, double px, double py);

		
	};

	extern Math math;
}

#endif