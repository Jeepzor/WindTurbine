#ifndef COLOR_H
#define COLOR_H
namespace wind {
	struct Color
	{
		Color(double red, double green, double blue, double alpha);

		double red;
		double green;
		double blue;
		double alpha;
	};
}

#endif