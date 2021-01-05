
#ifndef POLY_POINTS_H
#define POLY_POINTS_H

#include <vector>
#include "vec2.h"

namespace wind {
	struct PolyPoints
	{
		PolyPoints(double x1, double y1, double x2, double y2, double x3, double y3);
		std::vector <Vec2> getVertices();
		void applyRotation(double dt);
		void setRotation(double amount);
	private:
		std::vector <Vec2> vertices;

	};
}

#endif
