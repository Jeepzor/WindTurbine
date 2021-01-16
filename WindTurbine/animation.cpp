#include "animation.h"

namespace wind {
	Animation::Animation(std::string path, int amout_of_frames, double animation_rate) : Drawable::Drawable(path) {
		timer = 0;
		rate = animation_rate;
		frames = amout_of_frames;
		currentFrame = 1;
		frameWidth = width / frames;

		portion = { 0,0, frameWidth,height };
		destination = { 0, 0, frameWidth, height };
		originPoint = { frameWidth / 2, height / 2 };
	}

	Animation::~Animation() {
		SDL_DestroyTexture(asset);
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

	void Animation::updateDestination() {
		destination.w = static_cast<int>(frameWidth * scale + 0.5);
		destination.h = static_cast<int>(height * scale + 0.5);
	}

	void Animation::updateOriginPoint() {
		originPoint.x = static_cast<int>(frameWidth / 2 * scale + 0.5);
		originPoint.y = static_cast<int>(height / 2 * scale + 0.5);
	}

	void Animation::getDimensions(double& w, double& h) const {
		w = static_cast<int>(frameWidth * scale + 0.5);
		h = static_cast<int>(height * scale + 0.5);
	}

	void Animation::update(double dt) {
		timer += dt;
		if (timer >= rate) {
			timer = 0;
			incrementFrame();
		}
	}
}
