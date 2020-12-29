#include "animation.h"

namespace wind {
	Animation::Animation(std::string path, int amout_of_frames, double animation_rate) : wind::Image::Image(path) {
		timer = 0;
		rate = animation_rate;
		frames = amout_of_frames;
		currentFrame = 1;
		frameWidth = width / frames;

		portion = { 0,0, frameWidth,height };
		destination = { 0, 0, frameWidth, height };
		originPoint = { frameWidth / 2, height / 2 };
	}

	SDL_Rect* Animation::getPortion() {
		portion.x = frameWidth * (currentFrame - 1);
		return &portion;
	}

	void Animation::incrementFrame() {
		if (currentFrame < frames) {
			currentFrame += 1;
		}
		else {
			currentFrame = 1;
		}
	}

	void Animation::update(double dt) {
		timer += dt;
		if (timer >= rate) {
		std::cout << timer << "\n";
			timer = 0;
			incrementFrame();
		}
	}
}
