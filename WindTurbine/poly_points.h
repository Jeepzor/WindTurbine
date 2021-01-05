
#ifndef POLY_POINTS_H
#define POLY_POINTS_H

#include <vector>
#include "vec2.h"

namespace wind {
	struct PolyPoints
	{
		PolyPoints(double x, double y, double width, double height); //Rectangle shaped polygon
		PolyPoints(double x1, double y1, double x2, double y2, double x3, double y3);
		PolyPoints(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
		PolyPoints(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5);
		PolyPoints(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, double x6, double y6);
		PolyPoints(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, double x6, double y6, double x7, double y7);
		PolyPoints(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, double x6, double y6, double x7, double y7, double x8, double y8);

		std::vector <Vec2> getVertices();
	private:
		std::vector <Vec2> vertices;
	};
}

#endif
