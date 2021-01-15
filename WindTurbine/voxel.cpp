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
			setPosition(static_cast<int>(x + 0.5), static_cast<int>(y + 0.5 - i * scale * 0.85 + layers));

			//Draw it
			SDL_RenderCopyEx(wind::turbine.getRenderer(), getAsset(), getPortion(current_layer), getDestination(), getAngle(), getOriginPoint(), flip);
		}
	}

	//TODO: The following 3 functions need to be overriden in animation as well.
	void Voxel::updateDestination() {
		destination.w = width * scale;
		destination.h = layerHeight * scale;
	}

	void Voxel::updateOriginPoint() {
		originPoint.x = width / 2 * scale;
		originPoint.y = layerHeight / 2 * scale;
	}

	void Voxel::getDimensions(double& w, double& h) const {
		w = width * scale;
		h = layerHeight * scale;
	}
	//TODO: The above 3 functions need to be overriden in animation as well.


	Voxel::~Voxel() {
		SDL_DestroyTexture(asset);
	}

	SDL_Rect* Voxel::getPortion(int current_layer) {
		portion.y = layerHeight * (current_layer - 1);
		return &portion;
	}
}
