#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <string>
#include <SDL.h>

namespace wind {
	class Graphics {
	public:
		Graphics();
		void rectangle(double x, double y, double width, double height) const;
		void rectangle(std::string mode, double x, double y, double width, double height) const;
		void line(double x1, double y1, double x2, double y2) const;
		void circle(double x, double y, int radius) const;
		void circle(std::string mode, double x, double y, int radius) const;

		void setColor(Uint8 r, Uint8 g, Uint8 b);
		void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
		void clearColor();

		SDL_Color getColor() { return { red , green, blue, alpha}; };
		Uint8 getRed() const { return red; };
		Uint8 getGreen() const { return green; };
		Uint8 getBlue() const { return blue; };
		Uint8 getAlpha() const { return alpha; };
	private:
		void storeColors(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
		Uint8 red;
		Uint8 green;
		Uint8 blue;
		Uint8 alpha;
	};

	extern Graphics graphics;
}

#endif
