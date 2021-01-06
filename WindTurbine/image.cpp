#include <string>
#include <iostream>

#include <SDL_image.h>
#include <SDL.h>

#include "wind_turbine.h"
#include "image.h"

namespace wind {
	//Constructor
	Image::Image(std::string path) {
		surface = IMG_Load(path.c_str());

		width = surface->w;
		height = surface->h;
		angle = 0;
		flip = SDL_FLIP_NONE;

		portion = { 0,0, width, height };
		destination = { 0, 0, width, height };
		originPoint = { width / 2, height / 2 };
		asset = SDL_CreateTextureFromSurface(wind::turbine.getRenderer(), surface);
		SDL_FreeSurface(surface);
	}

	SDL_Rect* Image::getDestination() {
		return &destination;
	}

	SDL_Rect* Image::getPortion(){
		return NULL;
	}

	SDL_Point* Image::getOriginPoint() {
		return &originPoint;
	}

	//Destructor 
	Image::~Image() {
		std::cout << "destructor was called" << "\n";
		SDL_DestroyTexture(asset);
	}

	void Image::setFlip(bool x_axis, bool y_axis) {
		if (x_axis && y_axis) {
			flip = static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
		}
		else if (x_axis) {
			flip = SDL_FLIP_HORIZONTAL;
		}
		else if (y_axis) {
			flip = SDL_FLIP_VERTICAL;
		}
		else {
			flip = SDL_FLIP_NONE;
		}
	}

	void Image::setPosition(double x, double y) {
		destination.x = static_cast<int>(x + 0.5);
		destination.y = static_cast<int>(y + 0.5);
	};

	void Image::setAngle(double new_angle) {
		angle = new_angle;
	}

	SDL_Texture* Image::getAsset() const {
		return asset;
	}

	double Image::getAngle() const {
		return angle;
	}

	void Image::draw() {
		setColor();
		setPosition(0, 0);
		SDL_RenderCopyEx(wind::turbine.getRenderer(), getAsset(), getPortion(), getDestination(), angle, getOriginPoint(), flip);
	}

	void Image::draw(double x, double y) {
		setColor();
		setPosition(static_cast<int>(x + 0.5), static_cast<int>(y + 0.5));
		SDL_RenderCopyEx(wind::turbine.getRenderer(), getAsset(), getPortion(), getDestination(), angle, getOriginPoint(), flip);
	}

	void Image::setColor() {
		int r = wind::graphics.getRed();
		int g = wind::graphics.getGreen();
		int b = wind::graphics.getBlue();
		int a = wind::graphics.getAlpha();
		SDL_SetTextureAlphaMod(asset, a);
		SDL_SetTextureColorMod(asset, r, g, b);
	}

}