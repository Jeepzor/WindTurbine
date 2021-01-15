#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <SDL_image.h>
#include <string>

namespace wind {
	class Drawable {
	public:
		virtual ~Drawable() = 0;

		/// <summary>
		/// Render it on the screen at X: 0, Y: 0. Useful for backgrounds
		/// </summary>
		virtual void draw();

		/// <summary>
		/// Render it to the screen at specific coordinates
		/// </summary>
		/// <param name="x"> = X-Position</param>
		/// <param name="y"> = Y-Position</param>
		virtual void draw(double x, double y);

		/// <summary>
		/// Render it to the screen and override the global color. Useful for particles.
		/// </summary>
		/// <param name="x"> = X-Position</param>
		/// <param name="y"> = Y-Position</param>
		/// <param name="r"> = Red (0-255)</param>
		/// <param name="g"> = Green (0-255)</param>
		/// <param name="b"> = Blue (0-255)</param>
		/// <param name="a"> = Alpha (0-255)</param>
		void draw(double x, double y, double r, double g, double b, double a);

		/// <summary>
		/// Set the weather or not it should be mirrored on either the X or Y axis. 
		/// </summary>
		/// <param name="x_axis"> = Flip on X axis (true = mirror)</param>
		/// <param name="y_axis"> = Flip on Y axis (true = mirror)</param>
		void setFlip(bool x_axis, bool y_axis);

		/// <summary>
		/// Rotate it to a specific angle (in Radians)
		/// </summary>
		/// <param name="new_angle"> = New angle (in Radians)</param>
		void setAngle(double new_angle);
		
		/// <summary>
		/// Get the current rotation, in Radians
		/// </summary>
		/// <returns> Angle in Radians</returns>
		double getAngle() const;

		/// <summary>
		/// Set the width and height of the image to the passed in variables
		/// </summary>
		/// <param name="width"> = Variable which should be set to the width of the image</param>
		/// <param name="height"> = Variable which should be set to the height of the image</param>
		virtual void getDimensions(double &width, double &height) const;

		void setScale(double new_scale);

	protected:
		SDL_Rect* getDestination();
		virtual SDL_Rect* getPortion();
		SDL_Texture* getAsset() const;
		SDL_Point* getOriginPoint();

		Drawable(std::string path);

		Drawable(const Drawable& other) = delete;
		const Drawable& operator=(const Drawable& other) = delete;

		virtual void setPosition(double x, double y);
		virtual void setColor();
		virtual void updateDestination();
		virtual void updateOriginPoint();
		SDL_Surface* surface;
		SDL_Rect destination;
		SDL_Rect portion;
		SDL_Point originPoint;
		SDL_Texture* asset;
		SDL_RendererFlip flip;
		SDL_Renderer* testRenderer;

		double angle;
		double scale;

		int width;
		int height;

	};
}

#endif