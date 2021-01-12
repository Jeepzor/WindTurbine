
#ifndef MATH_H
#define MATH_H
#define PI 3.14159265

#include <iostream>
#include <string>
namespace wind {
	struct Math {
		Math();

		/// <summary>
		/// Returns the distance between two coordinates in pixels.
		/// </summary>
		/// <param name="x"> = First coordinate X</param>
		/// <param name="y"> = First coordinate Y</param>
		/// <param name="x2"> = Second coordinate X</param>
		/// <param name="y2"> = Second coordinate Y</param>
		/// <returns>Dinstance in pixels</returns>
		double distance(double x, double y, double x2, double y2) const;

		/// <summary>
		/// Returns the angle from one coordinate to a second one
		/// </summary>
		/// <param name="x"> = First coordinate X</param>
		/// <param name="y"> = First coordinate Y</param>
		/// <param name="x2"> = Second coordinate X</param>
		/// <param name="y2"> = Second coordinate Y</param>
		/// <returns></returns>
		double getAngle(double x, double y, double x2, double y2) const;

		/// <summary>
		/// Clamp a value between a minimum and maximum value
		/// </summary>
		/// <param name="min"> = The minimum allowed value</param>
		/// <param name="max"> = The maximum allowed value</param>
		/// <param name="value"> = The value that should be clamped</param>
		/// <returns>If it's greater than the maximum, it returns the maximum. If it's smaller than the minimum, it returns the minimum. Else it returns the value</returns>
		double clamp(double min, double max, double value) const;

		/// <summary>
		/// PI, the ratio of a circle's circumference to its diameter.
		/// </summary>
		/// <returns>3.14159265</returns>
		double pi() { return PI; };

		/// <summary>
		/// Returns a random value between 0 and 1, can be used to generate any random number.                   
		/// Example 1: (Number * random()) = value between 0 and the number.                    
		/// Example 2: ((Maximum - Minimum) * random() + Minimum) = Value between Maximum and Minimum.
		/// </summary>
		/// <returns>Value between 0 and 1</returns>
		double random() const;

		/// <summary>
		/// Checks if a point is inside a line
		/// </summary>
		/// <param name="x1"> = Line start X</param>
		/// <param name="y1"> = Line start Y</param>
		/// <param name="x2"> = Line end X</param>
		/// <param name="y2"> = Line end Y</param>
		/// <param name="px"> = Point X</param>
		/// <param name="py"> = Point Y</param>
		/// <returns></returns>
		bool pointInLine(double x1, double y1, double x2, double y2, double px, double py);

	};

	extern Math math;
}

#endif