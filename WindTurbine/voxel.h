#ifndef VOXEL_H
#define VOXEL_H

#include <string>

#include "drawable.h"

namespace wind {
	class Voxel : public Drawable {
	public:
		~Voxel()override;

		/// <summary>
		/// Used to instantiate new Voxel.
		/// </summary>
		/// <param name="path"> = Path to the image file</param>
		/// <param name="amount_of_layers"> = Number of Layers in the voxel (Z-axis)</param>
		/// <returns>Pointer to a Voxel</returns>
		static Voxel* getInstance(std::string path, int amount_of_layers) {
			return new Voxel(path, amount_of_layers);
		}

		/// <summary>
		/// Render the voxel on the screen
		/// </summary>
		/// <param name="x"> = X position on the sceen</param>
		/// <param name="y"> = Y position on the sceen</param>
		void draw(double x, double y) override;

		/// <summary>
		/// Set the dimensions of the Voxel to the passed in arguments
		/// </summary>
		/// <param name="w"> = Variable that will be set to the Width of the Voxel</param>
		/// <param name="h"> = Variable that will be set to the Height of the Voxel</param>
		void getDimensions(double& w, double& h) const;
		
	private:
		void updateDestination() override;
		void updateOriginPoint() override;
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