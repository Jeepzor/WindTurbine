#include "poly_points.h"
#include "point.h"

namespace wind {

	//Create a rectangle with polygon properties
	PolyPoints::PolyPoints(double x, double y, double width, double height) {
		vertices.push_back(Point(x, y));
		vertices.push_back(Point(x + width, y));
		vertices.push_back(Point(x + width, y + height));
		vertices.push_back(Point(x, y + height));
	}
	
	//Create a polygon with 3 vertices
	PolyPoints::PolyPoints(double x1, double y1, double x2, double y2, double x3, double y3) {
		vertices.push_back(Point(x1, y1));
		vertices.push_back(Point(x2, y2));
		vertices.push_back(Point(x3, y3));
	}
	
	//Create a polygon with 4 vertices
	PolyPoints::PolyPoints(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
		vertices.push_back(Point(x1, y1));
		vertices.push_back(Point(x2, y2));
		vertices.push_back(Point(x3, y3));
		vertices.push_back(Point(x4, y4));
	}
	
	//Create a polygon with 5 vertices
	PolyPoints::PolyPoints(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5) {
		vertices.push_back(Point(x1, y1));
		vertices.push_back(Point(x2, y2));
		vertices.push_back(Point(x3, y3));
		vertices.push_back(Point(x4, y4));
		vertices.push_back(Point(x5, y5));
	}
	
	//Create a polygon with 6 vertices
	PolyPoints::PolyPoints(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, double x6, double y6) {
		vertices.push_back(Point(x1, y1));
		vertices.push_back(Point(x2, y2));
		vertices.push_back(Point(x3, y3));
		vertices.push_back(Point(x4, y4));
		vertices.push_back(Point(x5, y5));
		vertices.push_back(Point(x6, y6));
	}	
	
	//Create a polygon with 7 vertices
	PolyPoints::PolyPoints(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, double x6, double y6, double x7, double y7) {
		vertices.push_back(Point(x1, y1));
		vertices.push_back(Point(x2, y2));
		vertices.push_back(Point(x3, y3));
		vertices.push_back(Point(x4, y4));
		vertices.push_back(Point(x5, y5));
		vertices.push_back(Point(x6, y6));
		vertices.push_back(Point(x7, y7));
	}
	
	//Create a polygon with 8 vertices
	PolyPoints::PolyPoints(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, double x6, double y6, double x7, double y7, double x8, double y8) {
		vertices.push_back(Point(x1, y1));
		vertices.push_back(Point(x2, y2));
		vertices.push_back(Point(x3, y3));
		vertices.push_back(Point(x4, y4));
		vertices.push_back(Point(x5, y5));
		vertices.push_back(Point(x6, y6));
		vertices.push_back(Point(x7, y7));
		vertices.push_back(Point(x8, y8));
	}

	std::vector <Point> PolyPoints::getVertices() {
		return vertices;
	}
}