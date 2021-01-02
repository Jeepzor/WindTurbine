#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <string>

namespace wind {
	class Graphics {
	public:
		Graphics();
		void rectangle(int x, int y, int width, int height) const;
		void rectangle(std::string mode, int x, int y, int width, int height) const;
		void line(int x1, int y1, int x2, int y2) const;
		void circle(int x, int y, int radius) const;
		void circle(std::string mode, int x, int y, int radius) const;

		void setColor(int r, int g, int b);
		void setColor(int r, int g, int b, int a);
		void clearColor();

		int getRed() const { return red; };
		int getGreen() const { return green; };
		int getBlue() const { return blue; };
		int getAlpha() const { return alpha; };
	private:
		void storeColors(int r, int g, int b, int a);
		int red;
		int green;
		int blue;
		int alpha;
	};

	extern Graphics graphics;
}

#endif
