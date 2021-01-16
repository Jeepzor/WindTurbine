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

	Font::~Font() {
		TTF_CloseFont(font);
	}

	void Font::draw(std::string text, double x, double y) {
		draw(text, x, y, 0);
	}
	
	void Font::draw(std::string text, double x, double y, double angle) {
		surface = TTF_RenderText_Solid(font, text.c_str(), graphics.getColor());
		texture = SDL_CreateTextureFromSurface(turbine.getRenderer(),surface);
		destination = { static_cast<int>(x + 0.5),  static_cast<int>(y + 0.5), surface->w, surface->h };
		SDL_FreeSurface(surface);
		double angle_radians = angle * 57.29578; // Translate from Degrees to Radians
		SDL_RenderCopyEx(turbine.getRenderer(), texture, NULL, &destination, angle_radians, NULL, SDL_FLIP_NONE);
		SDL_DestroyTexture(texture);
	}

}
