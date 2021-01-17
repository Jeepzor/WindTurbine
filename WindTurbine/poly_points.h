
#ifndef POLY_POINTS_H
#define POLY_POINTS_H

#include <vector>
#include "point.h"

namespace wind {
	struct PolyPoints
	{
		//Create a rectangle with polygon properties
		PolyPoints(double x, double y, double width, double height); 

		//Create a polygon with 3 vertices
		PolyPoints(double x1, double y1, double x2, double y2, double x3, double y3);

		//Create a polygon with 4 vertices
		PolyPoints(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);

		//Create a polygon with 5 vertices
		PolyPoints(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5);

		//Create a polygon with 6 vertices
		PolyPoints(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, double x6, double y6);

		//Create a polygon with 7 vertices
		PolyPoints(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, double x6, double y6, double x7, double y7);

		//Create a polygon with 8 vertices
		PolyPoints(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, double x6, double y6, double x7, double y7, double x8, double y8);

		/// <summary>
		/// Get the vertices of the vector
		/// </summary>
		/// <returns>A vector containing all PolyPoints of the polygon.</returns>
		std::vector <Point> getVertices();
	private:
		std::vector <Point> vertices;
	};
}

#endif
