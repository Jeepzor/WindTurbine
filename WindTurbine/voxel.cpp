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
		for (int i = 0; i < layers; i++)
		{
			SDL_SetTextureColorMod(asset, 255 - layers * 5 + i * 5, 255 - layers * 5 + i * 5, 255 - layers * 5 + i * 5);
			int current_layer = layers - i;
			setPosition(static_cast<int>(x + 0.5), static_cast<int>(y + 0.5 - i * scale * 0.85 + layers));
			SDL_RenderCopyEx(wind::turbine.getRenderer(), getAsset(), getPortion(current_layer), getDestination(), getAngle(), getOriginPoint(), flip);
		}
	}

	//The following 3 functions need to be overriden in animation as well.
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
	//The above 3 functions need to be overriden in animation as well.


	Voxel::~Voxel() {
		SDL_DestroyTexture(asset);
	}

	SDL_Rect* Voxel::getPortion(int current_layer) {
		portion.y = layerHeight * (current_layer - 1);
		return &portion;
	}
}
