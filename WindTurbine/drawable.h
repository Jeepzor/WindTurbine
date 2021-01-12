#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <SDL_image.h>
#include <string>

namespace wind {
	class Drawable {
	public:
		virtual ~Drawable() = 0;

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
		Drawable(std::string path);

		Drawable(const Drawable& other) = delete;
		const Drawable& operator=(const Drawable& other) = delete;

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