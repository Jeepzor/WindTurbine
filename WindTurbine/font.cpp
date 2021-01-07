#include <iostream>
#include <stdexcept>

#include "font.h"
#include "wind_turbine.h"
#include "graphics.h"

namespace wind {
	Font::Font(std::string path, int font_size) {
		size = font_size;
		font = TTF_OpenFont(path.c_str(), size);
		destination = { 0, 0, 0, 0 };
		if (!font) {
			std::cerr << "Error: Font did not load properly!" << "\n";
			throw std::runtime_error("Error: Font did not load properly!");
		}
	}

	void Font::draw(std::string text, double x, double y) {
		surface = TTF_RenderText_Solid(font, text.c_str(), graphics.getColor());
		texture = SDL_CreateTextureFromSurface(turbine.getRenderer(),surface);
		destination = { static_cast<int>(x + 0.5),  static_cast<int>(y + 0.5), surface->w, surface->h };
		SDL_FreeSurface(surface);
		SDL_RenderCopy(turbine.getRenderer(), texture, NULL, &destination);
		SDL_DestroyTexture(texture);
	}

}
