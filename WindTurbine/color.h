#ifndef COLOR_H
#define COLOR_H
namespace wind {
	struct Color
	{
		// (0-255)
		Color(double red, double green, double blue, double alpha); 

		double red; // (0-255)
		double green; // (0-255)
		double blue; // (0-255)
		double alpha; // (0-255)
	};
}

#endif