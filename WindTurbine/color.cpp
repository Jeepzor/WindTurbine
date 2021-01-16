#include "color.h";

namespace wind {
	Color::Color(double r, double g, double b, double a) {
		red = r;
		green = g;
		blue = b;
		alpha = a;
	}

	Color::Color() {
		red = 255;
		green = 255;
		blue = 255;
		alpha = 255;
	}
}