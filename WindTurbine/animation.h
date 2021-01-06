#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>

#include "image.h"

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
		double rate;
		double timer;
	};

}
#endif