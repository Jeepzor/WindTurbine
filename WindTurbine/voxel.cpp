#include "voxel.h"
#include "wind_turbine.h"
#include "graphics.h"

namespace wind {
	Voxel::Voxel(std::string path, int amout_of_layers) : Drawable::Drawable(path) {
		
		layers = amout_of_layers;
		layerHeight = height / layers;

		portion = { 0,0, width,layerHeight };
		destination = { 0, 0, width, layerHeight };
		originPoint = { width / 2, layerHeight / 2 };
	}

	Voxel::~Voxel() {
		SDL_DestroyTexture(asset);
	}

	void Voxel::draw(double x, double y) {
		//Loop through all layers and draw them individually
		double shading = 255.0 / static_cast<double>(layers);
		for (int i = 0; i < layers; i++)
		{
			
			//Apply some very basic "shading", making lower layers slightly darker
			SDL_SetTextureColorMod(asset, 0 + i * shading, 0 + i * shading, 0 + i * shading);
			
			//Reverse the order of drawing
			int current_layer = layers - i;

			//Offset the draw position by the layer number
			setPosition(x, y - i * scale + layers);

			//Draw it
			SDL_RenderCopyEx(wind::turbine.getRenderer(), getAsset(), getPortion(current_layer), getDestination(), getAngle(), getOriginPoint(), flip);
		}
	}

	void Voxel::updateDestination() {
		destination.w = static_cast<int>(width * scale + 0.5);
		destination.h = static_cast<int>(layerHeight * scale + 0.5);
	}

	void Voxel::updateOriginPoint() {
		originPoint.x = static_cast<int>(width / 2 * scale + 0.5);
		originPoint.y = static_cast<int>(layerHeight / 2 * scale + 0.5);
	}

	void Voxel::getDimensions(double& w, double& h) const {
		w = static_cast<int>(width * scale + 0.5);
		h = static_cast<int>(layerHeight * scale + 0.5);
	}

	SDL_Rect* Voxel::getPortion(int current_layer) {
		portion.y = layerHeight * (current_layer - 1);
		return &portion;
	}
}
