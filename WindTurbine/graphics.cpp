#include "wind_turbine.h"
#include "graphics.h"

namespace wind {

	Graphics::Graphics() {

	}

	void Graphics::rectangle(std::string mode, int x, int y, int width, int height) {
		SDL_Rect dimensions = {x, y, width, height};
		//SDL_SetRenderDrawColor(wind::turbine->getRenderer, 255, 255, 255, 255);
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

	Graphics graphics;
}