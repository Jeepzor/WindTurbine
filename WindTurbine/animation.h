#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL_image.h>
#include <string>

#include "wind_turbine.h"

namespace wind {
	class Animation : public wind::Image {
	public:
		Animation(std::string path, int amout_of_frames, double animation_rate);
		void update(double dt);
		void incrementFrame();

	private:
		SDL_Rect* getPortion() override;
		int frames;
		int currentFrame;
		int frameWidth;
		double angle;
		double rate;
		double timer;
	};

}
#endif