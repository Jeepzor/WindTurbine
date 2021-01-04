#include "poly_points.h"
#include "vec2.h"

namespace wind {
	// TODO, add vec2 math via operator overloading
	PolyPoints::PolyPoints(double x1, double y1, double x2, double y2, double x3, double y3) {
		vertices.push_back(Vec2(x1, y1));
		vertices.push_back(Vec2(x2, y2));
		vertices.push_back(Vec2(x3, y3));
	}

	std::vector <Vec2> PolyPoints::getVertices() {
		return vertices;
	}
}