#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>

#include "drawable.h"

namespace wind {
	class Animation : public Drawable {
	public:
		~Animation()override;
		void update(double dt);
		void incrementFrame();

		static Animation* getInstance(std::string path, int amount_of_frames, double animation_rate) {
			return new Animation(path, amount_of_frames, animation_rate);
		}

	private:
		Animation(std::string path, int amout_of_frames, double animation_rate);
		Animation(const Animation& other) = delete;
		const Animation& operator=(const Animation& other) = delete;

		SDL_Rect* getPortion() override;
		int frames;
		int currentFrame;
		int frameWidth;
		double rate;
		double timer;
	};

}
#endif