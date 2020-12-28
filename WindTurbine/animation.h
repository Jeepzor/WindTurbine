#ifndef ANIMATION_H
#define ANIMATION_H
#include <SDL_image.h>
#include <string>

#include "wind_turbine.h"

namespace wind {
	class Animation {
	public:
		Animation(std::string path);
		Animation(const Animation& source);
		Animation& operator = (const Animation& source);
		Animation();
		~Animation();

		void draw();
		void draw(int x, int y);
		void draw(int x, int y, int r, int g, int b);
		void draw(int x, int y, int r, int g, int b, int a);
		void setFlip(bool x_axis, bool y_axis);
		void setAngle(double new_angle);

		double getAngle();
		int getWidth();
		int getHeight();
		SDL_Rect* getDestination();
		SDL_Texture* getAsset();

	private:
		void setPosition(int, int);
		SDL_Surface* surface;
		SDL_Rect destination;
		SDL_Texture* asset;
		SDL_RendererFlip flip;

		int width;
		int height;
		double angle;

		std::string assetPath;
	};
}

#endif