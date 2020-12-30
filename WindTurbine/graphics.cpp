#include "wind_turbine.h"
#include "graphics.h"

namespace wind {

	Graphics::Graphics() {
		red = 255;
		green = 255;
		blue = 255;
		alpha = 255;
	}

	void Graphics::rectangle(std::string mode, int x, int y, int width, int height) {
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
	
	void Graphics::line(int x1, int y1, int x2, int y2) {
		SDL_RenderDrawLine(wind::turbine.getRenderer(),x1, y1, x2, y2);
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