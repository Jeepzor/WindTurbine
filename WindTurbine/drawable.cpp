#include <string>
#include <iostream>

#include "drawable.h"
#include "graphics.h"
#include "wind_turbine.h"

namespace wind {
	//Constructor
	Drawable::Drawable(std::string path) {
		surface = IMG_Load(path.c_str());

		width = surface->w;
		height = surface->h;
		angle = 0;
		flip = SDL_FLIP_NONE;

		portion = { 0,0, width, height };
		destination = { 0, 0, width, height};
		originPoint = { width / 2, height / 2 };
		asset = SDL_CreateTextureFromSurface(wind::turbine.getRenderer(), surface);
		SDL_FreeSurface(surface);
	}

	SDL_Rect* Drawable::getDestination() {
		return &destination;
	}

	SDL_Rect* Drawable::getPortion(){
		return NULL;
	}

	SDL_Point* Drawable::getOriginPoint() {
		return &originPoint;
	}

	//Destructor 
	Drawable::~Drawable() {
		SDL_DestroyTexture(asset);
	}

	void Drawable::setFlip(bool x_axis, bool y_axis) {
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

	void Drawable::setPosition(double x, double y) {
		destination.x = static_cast<int>(x + 0.5);
		destination.y = static_cast<int>(y + 0.5);
	};

	void Drawable::setAngle(double new_angle) {
		angle = new_angle;
	}

	void Drawable::setScale(double new_scale) {
		scale = new_scale;
		updateOriginPoint();
		updateDestination();
	}

	void Drawable::setScale(double new_scale, bool ignoreOrigin) {
		if (ignoreOrigin){
			scale = new_scale;
			updateDestination();
		}
		else {
			setScale(new_scale);
		}
	}

	void Drawable::updateDestination() {
		destination.w = static_cast<int>(width * scale + 0.5);
		destination.h = static_cast<int>(height * scale + 0.5);
	}
	
	void Drawable::updateOriginPoint() {
		originPoint.x = static_cast<int>(width / 2 * scale + 0.5);
		originPoint.y = static_cast<int>(height / 2 * scale + 0.5);
	}

	SDL_Texture* Drawable::getAsset() const {
		return asset;
	}

	double Drawable::getAngle() const {
		return angle * 57.29578;
	}

	void Drawable::getDimensions(double &w, double &h) const {
		w = width;
		h = height;
	}

	void Drawable::draw() {
		setColor();
		setPosition(0, 0);
		SDL_RenderCopyEx(wind::turbine.getRenderer(), getAsset(), getPortion(), getDestination(), getAngle(), getOriginPoint(), flip);
	}

	void Drawable::draw(double x, double y) {
		setColor();
		setPosition(static_cast<int>(x + 0.5), static_cast<int>(y + 0.5));
		SDL_RenderCopyEx(wind::turbine.getRenderer(), getAsset(), getPortion(), getDestination(), getAngle(), getOriginPoint(), flip);
	}
	
	//Mainly for particles.
	void Drawable::draw(double x, double y, double r, double g, double b, double a) {
		SDL_SetTextureAlphaMod(asset, a);
		SDL_SetTextureColorMod(asset, r, g, b);
		destination.x = static_cast<int>(x + 0.5);
		destination.y = static_cast<int>(y + 0.5);
		SDL_RenderCopyEx(wind::turbine.getRenderer(), asset, NULL, &destination, angle, NULL, flip);
	}

	void Drawable::setColor() {
		SDL_SetTextureAlphaMod(asset, wind::graphics.getAlpha());
		SDL_SetTextureColorMod(asset, wind::graphics.getRed(), wind::graphics.getGreen(), wind::graphics.getBlue());
	}

}