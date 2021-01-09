#ifndef IMAGE_H
#define IMAGE_H
#include <SDL_image.h>
#include <string>

namespace wind {
	class Image {
	public:
		Image(std::string path);
		~Image();

		virtual void draw();
		void draw(double x, double y);
		void draw(double x, double y, double r, double g, double b, double a);
		void setFlip(bool x_axis, bool y_axis);
		void setAngle(double new_angle);
		
		double getAngle() const;
		
		SDL_Rect* getDestination();
		virtual SDL_Rect* getPortion();
		SDL_Texture* getAsset() const;
		SDL_Point* getOriginPoint();

	protected:
		void incrementFrame();
		virtual void setPosition(double x, double y);
		virtual void setColor();
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