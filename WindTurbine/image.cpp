#include <string>
#include <iostream>

#include <SDL_image.h>
#include <SDL.h>

#include "wind_turbine.h"
#include "image.h"

namespace wind {
	//Constructor
	Image::Image(std::string path) {
		std::cout << "normal constructor called" << "\n";
		assetPath = path;
		surface = IMG_Load(path.c_str());
		width = surface->w;
		height = surface->h;
		angle = 0;
		destination = { 0, 0, width, height };
		portion = { 0,0,width,height };
		originPoint = { width / frames,height / 2 };
		frames = 1;
		asset = SDL_CreateTextureFromSurface(wind::turbine.getRenderer(), surface);
		SDL_FreeSurface(surface);
	}
	
	//Constructor for animated images: Move to own class, Animation, which inherits Image.
	Image::Image(std::string path, int amout_of_frames, int rate) {
		std::cout << "normal constructor called" << "\n";
		assetPath = path;
		surface = IMG_Load(path.c_str());
		width = surface->w;
		height = surface->h;
		angle = 0;
		frames = amout_of_frames;
		destination = { 0, 0, width / frames, height };
		portion = { 0,0,width / frames, height };
		originPoint = { width / frames,height / 2 };
		asset = SDL_CreateTextureFromSurface(wind::turbine.getRenderer(), surface);
		SDL_FreeSurface(surface);
	}

	// Default Constructor
	Image::Image() {
		std::cout << "default constructor called" << "\n";
		assetPath = "";
		surface = nullptr;
		width = 0;
		height = 0;
		angle = 0;
		frames = 1;
		frameWidth = width / frames;
		destination = { 0, 0, frameWidth, height };
		portion = { 0,0,width / frames / 2,height };
		originPoint = { width / frames,height / 2 };
		asset = nullptr;
	}

	//Copy Constructor
	Image::Image(const Image& source) {
		std::cout << "copy constructor was called" << "\n";
		assetPath = source.assetPath;
		surface = IMG_Load(assetPath.c_str());
		width = source.width;
		height = source.height;
		angle = source.angle;
		frames = source.frames;
		frameWidth = width / frames;
		portion = { 0,0, frameWidth,height };
		destination = { 0, 0, width / frames, height };
		originPoint = { width / frames,height / 2 };
		asset = SDL_CreateTextureFromSurface(wind::turbine.getRenderer(), surface);
		SDL_FreeSurface(surface);
	}

	//Assignement Operator
	Image& Image::operator = (const Image& source) {
		std::cout << "assignment operator was called" << "\n";
		if (this == &source) {
			return *this; //"This" is a pointer, therefor it needs to be de-referenced
		}
		SDL_DestroyTexture(asset);
		assetPath = source.assetPath;
		surface = IMG_Load(assetPath.c_str());
		width = source.width;
		height = source.height;
		angle = source.angle;
		frames = source.frames;
		frameWidth = width / frames;
		portion = { 0,0, frameWidth,height };
		destination = { 0, 0, width / frames, height };
		originPoint = { width / frames,height / 2 };
		asset = SDL_CreateTextureFromSurface(wind::turbine.getRenderer(), surface);
		SDL_FreeSurface(surface);
		return *this;
	}

	SDL_Rect* Image::getDestination() {
		return &destination;
	}
	
	SDL_Rect* Image::getPortion() {
		return &portion;
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
		else if(x_axis) {
			flip = SDL_FLIP_HORIZONTAL;
		}
		else if(y_axis) {
			flip = SDL_FLIP_VERTICAL;
		}
		else {
			flip = SDL_FLIP_NONE;
		}
	}

	void Image::setPosition(int x, int y) {
		destination.x = x;
		destination.y = y;
	};

	void Image::setAngle(double new_angle) {
		angle = new_angle;
	}

	SDL_Texture* Image::getAsset() {
		return asset;
	}

	double Image::getAngle() {
		return angle;
	}

	void Image::draw() {
		setPosition(0, 0);
		SDL_RenderCopyEx(wind::turbine.getRenderer(), getAsset(), getPortion(), getDestination(), angle, getOriginPoint(), flip);
	}

	void Image::draw(int x, int y) {
		setPosition(x, y);
		SDL_RenderCopyEx(wind::turbine.getRenderer(), getAsset(), getPortion(), getDestination(), angle, getOriginPoint(), flip);
	}

	void Image::draw(int x, int y, int r, int g, int b) {
		SDL_SetTextureColorMod(asset, r, g, b);
		setPosition(x, y);
		SDL_RenderCopyEx(wind::turbine.getRenderer(), getAsset(), getPortion(), getDestination(), angle, getOriginPoint(), flip);
	}

	void Image::draw(int x, int y, int r, int g, int b, int a) {
		SDL_SetTextureAlphaMod(asset, a);
		SDL_SetTextureColorMod(asset, r, g, b);
		setPosition(x, y);
		SDL_RenderCopyEx(wind::turbine.getRenderer(), getAsset(), getPortion(), &destination, angle, getOriginPoint(), flip);
	}
}
