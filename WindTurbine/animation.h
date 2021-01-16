#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>

#include "drawable.h"

namespace wind {
	class Animation : public Drawable {
	public:
		~Animation()override;

		/// <summary>
		/// Updates the animation, looping through it's frames.
		/// </summary>
		/// <param name="dt"> = Delta Time</param>
		void update(double dt);

		/// <summary>
		/// Used to instantiate new Animations.
		/// </summary>
		/// <param name="path"> = Path to the image file</param>
		/// <param name="amount_of_frames"> = Number of frames in the animation</param>
		/// <param name="animation_rate"> = Time (in milliseconds) between frames</param>
		/// <returns>Pointer to an Animation</returns>
		static Animation* getInstance(std::string path, int amount_of_frames, double animation_rate) {
			return new Animation(path, amount_of_frames, animation_rate);
		}

	private:
		void incrementFrame();
		Animation(std::string path, int amout_of_frames, double animation_rate);
		Animation(const Animation& other) = delete;
		const Animation& operator=(const Animation& other) = delete;

		void getDimensions(double& w, double& h) const override;

		void updateOriginPoint() override;

		void updateDestination() override;

		SDL_Rect* getPortion() override;
		int frames;
		int currentFrame;
		int frameWidth;
		double rate;
		double timer;
	};

}
#endif