#ifndef IMAGE_H
#define IMAGE_H
#include <SDL_image.h>
#include <string>

namespace wind {
	class Image {
	public:
		Image(std::string path);
		~Image();

		void draw();
		void draw(int x, int y);
		void draw(int x, int y, int r, int g, int b);
		void draw(int x, int y, int r, int g, int b, int a);
		void setFlip(bool x_axis, bool y_axis);
		void setAngle(double new_angle);
		
		double getAngle();
		
		SDL_Rect* getDestination();
		virtual SDL_Rect* getPortion();
		SDL_Texture* getAsset();
		SDL_Point* getOriginPoint();

	protected:
		void incrementFrame();
		void setPosition(int, int);
		SDL_Surface* surface;
		SDL_Rect destination;
		SDL_Rect portion;
		SDL_Point originPoint;
		SDL_Texture* asset;
		SDL_RendererFlip flip;

		double angle;

		int width;
		int height;

	};
}

#endif