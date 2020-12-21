#include <string>
#include <iostream>

#include <SDL_image.h>
#include <SDL.h>

#include "wind_turbine.h"
#include "image.h"

//Constructor
Image::Image(std::string path) {
	std::cout << "normal constructor called" << "\n";
	assetPath = path;
	surface = IMG_Load(path.c_str());
	width = surface->w;
	height = surface->h;
	destination = { 0, 0, width, height };
	asset = SDL_CreateTextureFromSurface(wind_turbine::engine.getRenderer(), surface);
	SDL_FreeSurface(surface);
}
	
// Default Constructor
Image::Image() {
	std::cout << "default constructor called" << "\n";
	assetPath = "";
	surface = nullptr;
	width = 0;
	height = 0;
	destination = { 0, 0, width, height };
	asset = nullptr;
}

//Copy Constructor
Image::Image(const Image& source) {
	std::cout << "copy constructor was called" << "\n";
	assetPath = source.assetPath;
	surface = IMG_Load(assetPath.c_str());
	width = source.width;
	height = source.height;
	destination = { 0, 0, width, height };
	asset = SDL_CreateTextureFromSurface(wind_turbine::engine.getRenderer(), surface);
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
	destination = { 0, 0, width, height };
	asset = SDL_CreateTextureFromSurface(wind_turbine::engine.getRenderer(), surface);
	SDL_FreeSurface(surface);
	return *this;
}

//Destructor 
Image::~Image() {
	SDL_DestroyTexture(asset);
}

int Image::getWidth() {
	return width;
}

int Image::getHeight() {
	return height;
}

void Image::setPosition(int x, int y) {
	destination.x = x;
	destination.y = y;
};

SDL_Texture* Image::getAsset() {
	return asset;
}


void Image::draw(int x, int y) {
	setPosition(x, y);
	SDL_RenderCopy(wind_turbine::engine.getRenderer(), getAsset(), NULL, &destination);
}
