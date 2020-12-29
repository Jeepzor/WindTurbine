#ifndef IMAGE_H
#define IMAGE_H
#include <SDL_image.h>
#include <string>

namespace wind {
	class Image {
	public:
		Image(std::string path);
		Image(std::string path, int amout_of_frames, double animation_rate);
		Image(const Image& source);
		Image& operator = (const Image& source);
		Image();
		~Image();

		void animate(double dt);

		void draw();
		void draw(int x, int y);
		void draw(int x, int y, int r, int g, int b);
		void draw(int x, int y, int r, int g, int b, int a);
		void setFlip(bool x_axis, bool y_axis);
		void setAngle(double new_angle);
		
		double getAngle();
		
		SDL_Rect* getDestination();
		SDL_Rect* getPortion();
		SDL_Texture* getAsset();
		SDL_Point* getOriginPoint();

	private:
		void incrementFrame();
		void setPosition(int, int);
		SDL_Surface* surface;
		SDL_Rect destination;
		SDL_Rect portion;
		SDL_Point originPoint;
		SDL_Texture* asset;
		SDL_RendererFlip flip;

		int frames;
		int currentFrame;
		int frameWidth;
		int width;
		int height;
		double angle;
		double rate;
		double timer;
		
		std::string assetPath;
	};
}

#endif