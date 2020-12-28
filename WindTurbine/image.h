#ifndef IMAGE_H
#define IMAGE_H
#include <SDL_image.h>
#include <string>

namespace wind {
	class Image {
	public:
		Image(std::string path);
		Image(const Image& source);
		Image& operator = (const Image& source);
		Image();
		~Image();

		void draw();
		void draw(int x, int y);
		void draw(int x, int y, int r, int g, int b);
		void draw(int x, int y, int r, int g, int b, int a);
		void setFlip(bool x_axis, bool y_axis);
		void setPosition(int, int);
		void setAngle(double new_angle);
		
		double getAngle();
		int getWidth();
		int getHeight();
		SDL_Rect* getDestination();
		SDL_Texture* getAsset();

	private:
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