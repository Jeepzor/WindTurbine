#ifndef VOXEL_H
#define VOXEL_H

#include <string>

#include "drawable.h"

namespace wind {
	class Voxel : public Drawable {
	public:
		~Voxel()override;

		/// <summary>
		/// Updates the animation, looping through it's frames.
		/// </summary>
		/// <param name="dt"> = Delta Time</param>

		/// <summary>
		/// Used to instantiate new Animations.
		/// </summary>
		/// <param name="path"> = Path to the image file</param>
		/// <param name="amount_of_frames"> = Number of Layers in the voxel</param>
		/// <returns>Pointer to an Animation</returns>
		static Voxel* getInstance(std::string path, int amount_of_layers) {
			return new Voxel(path, amount_of_layers);
		}

		void draw(double x, double y) override;
		void getDimensions(double& w, double& h) const;
		
		void updateDestination() override;
		void updateOriginPoint() override;
	private:
		Voxel(std::string path, int amount_of_layers);
		Voxel(const Voxel& other) = delete;
		const Voxel& operator=(const Voxel& other) = delete;

		void updatePortion();
		SDL_Rect* getPortion(int current_layer);
		int layers;
		int layerHeight;
	};

}
#endif