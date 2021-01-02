#include <math.h>

#include "wind_turbine.h"
#include "graphics.h"

#define PI 3.14159265

namespace wind {

	Graphics::Graphics() {
		red = 255;
		green = 255;
		blue = 255;
		alpha = 255;
	}

	void Graphics::rectangle(int x, int y, int width, int height) const {
		rectangle("fill", x, y, width, height);
	}

	void Graphics::rectangle(std::string mode, int x, int y, int width, int height) const {
		SDL_Rect dimensions = {x, y, width, height};
		if (mode == "fill") {
			SDL_RenderFillRect(wind::turbine.getRenderer(), &dimensions);
		}
		else if (mode == "line") {
			SDL_RenderDrawRect(wind::turbine.getRenderer(), &dimensions);
		}
		else {
			std::cerr << "Error: " + mode + "' is not a valid draw mode!" << "\n";
		}
	}
	
	void Graphics::line(int x1, int y1, int x2, int y2) const {
		SDL_RenderDrawLine(wind::turbine.getRenderer(),x1, y1, x2, y2);
	}
	
	void Graphics::circle(int x, int y, int radius) const {
		circle("fill", x, y, radius);
	}
	
	void Graphics::circle(std::string mode, int x, int y, int radius) const {
		int cx = x;
		int cy = y;
		if (mode == "line") {
			double prev_x = x;
			double prev_y = y;
			
			for (int i = 0; i < 30; i++)
			{
				if (i == 0) {
					double angle = -1 * PI / 15;
					prev_x = x + radius * std::cos(angle);
					prev_y = y + radius * std::sin(angle);
				}
				double angle = i * PI / 15;
				double x2 = x + radius * std::cos(angle);
				double y2 = y + radius * std::sin(angle);
				SDL_RenderDrawLine(wind::turbine.getRenderer(), prev_x, prev_y, x2, y2);

				prev_x = x2;
				prev_y = y2;
			}
		}
		else if (mode == "fill") {
			//rectangle("line", x - radius, y - radius, radius * 2, radius * 2);// Use rectangle to visualize the area
			//For efficiency we want to calculate 1/4 of the circle, and then through the magic of symetry fill out the rest.
			//We choose the top right quadrant.
			int start_x = cx;
			int start_y = cy - radius;
			int end_x = start_x + radius * 2;
			int end_y = start_y + radius;
			//rectangle("line", start_x, start_y, radius, radius); //Use rectangle to visualize the slice
			for (int i = start_x; i <= end_x; i++) {
				for (int j = start_y; j <= end_y; j++) {
					if (((i - cx) * (i - cx) + (j - cy) * (j - cy) - radius * radius) <= 0) {
						SDL_RenderDrawPoint(wind::turbine.getRenderer(), i, j); // this is the validated point
						//Below we mirror these points, this can probably be improved.
						SDL_RenderDrawPoint(wind::turbine.getRenderer(), end_x - i + start_x - radius * 2, j); // mirrored on X axis
						SDL_RenderDrawPoint(wind::turbine.getRenderer(), i, end_y - j + start_y + radius); // mirrored on Y axis
						SDL_RenderDrawPoint(wind::turbine.getRenderer(), end_x - i + start_x - radius * 2, end_y - j + start_y + radius); // mirrored on X & Y  axis
					}
				}
			}
		}
	}

	void Graphics::setColor(int r, int g, int b) {
		storeColors(r, g, b, 255);
		SDL_SetRenderDrawColor(wind::turbine.getRenderer(), r, b, g, 255);
	}
	
	void Graphics::setColor(int r, int g, int b, int a) {
		storeColors(r, g, b, a);
		SDL_SetRenderDrawColor(wind::turbine.getRenderer(), r, b, g, a);
	}
	
	void Graphics::clearColor() {
		storeColors(255, 255, 255, 255);
		SDL_SetRenderDrawColor(wind::turbine.getRenderer(), 255, 255, 255, 255);
	}

	void Graphics::storeColors(int r, int g, int b, int a) {
		red = r;
		green = g;
		blue = b;
		alpha = a;
	}

	Graphics graphics;
}