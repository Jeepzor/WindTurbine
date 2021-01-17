#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <string>
#include <SDL.h>

namespace wind {
	class Graphics {
	public:
		Graphics();

		/// <summary>
		/// Render a solid rectangle on the screen
		/// </summary>
		/// <param name="x"> = X position for the left side</param>
		/// <param name="y"> = Y position for the top side</param>
		/// <param name="width"> = Width in pixels</param>
		/// <param name="height"> = Height in pixels</param>
		void rectangle(double x, double y, double width, double height) const;

		/// <summary>
		/// Render either a solid or outlined rectangle on the screen
		/// </summary>
		/// <param name="mode"> = "fill" for solid, "line" for outline</param>
		/// <param name="x"> X position for the left side</param>
		/// <param name="y"> = Y position for the top side</param>
		/// <param name="width"> = Width in pixels</param>
		/// <param name="height"> = Height in pixels</param>
		void rectangle(std::string mode, double x, double y, double width, double height) const;

		/// <summary>
		/// Render a line between two coordinates
		/// </summary>
		/// <param name="x1"> = X position for the first point in the line</param>
		/// <param name="y1"> = Y position for the first point in the line</param>
		/// <param name="x2"> = X position for the second point in the line</param>
		/// <param name="y2"> = Y position for the second point in the line</param>
		void line(double x1, double y1, double x2, double y2) const;

		/// <summary>
		/// Render a solid circle on the screen
		/// </summary>
		/// <param name="x"> = X position for the center of the circle</param>
		/// <param name="y"> = Y position for the center of the circle</param>
		/// <param name="radius"> = Length of the circles radius in pixels</param>
		void circle(double x, double y, int radius) const;

		/// <summary>
		/// Render either a solid or outlined circle on the screen
		/// </summary>
		/// <param name="mode"> = "fill" for solid, "line" for outline</param>
		/// <param name="x"> = X position for the center of the circle</param>
		/// <param name="y"> = Y position for the center of the circle</param>
		/// <param name="radius"> = Length of the circles radius in pixels</param>
		void circle(std::string mode, double x, double y, int radius) const;

		/// <summary>
		/// Set the current color for all Images, animations, Voxels and Shapes. 
		/// This automatically gets reset to white with full opacity (255,255,255,255) each new frame.
		/// You can manually reset it using "clearColor"
		/// or by passing in a new value.
		/// </summary>
		/// <param name="r"> = Red value (0-255)</param>
		/// <param name="g"> = Green value (0-255)</param>
		/// <param name="b"> = Blue value (0-255)</param>
		void setColor(double r, double g, double b);

		/// <summary>
		/// Set the current color for all Images, animations, Voxels and Shapes. 
		/// This automatically gets reset to white with full opacity (255,255,255,255) each new frame.
		/// You can manually reset it using "clearColor"
		/// or by passing in a new value.
		/// </summary>
		/// <param name="r"> = Red value (0-255)</param>
		/// <param name="g"> = Green value (0-255)</param>
		/// <param name="b"> = Blue value (0-255)</param>
		/// <param name="a"> = Alpha value (0-255)</param>
		void setColor(double r, double g, double b, double a);

		/// <summary>
		/// Resets the color back to white with full opacity (255,255,255,255)
		/// </summary>
		void clearColor();

		/// <summary>
		/// Get the currently set color 
		/// </summary>
		/// <returns>SLD_Color {red, green, blue, alpha}</returns>
		SDL_Color getColor() const { return { red , green, blue, alpha}; };

		/// <summary>
		/// Get the currently set Red value (0-255)
		/// </summary>
		Uint8 getRed() const { return red; };

		/// <summary>
		/// Get the currently set Green value (0-255)
		/// </summary>
		Uint8 getGreen() const { return green; };

		/// <summary>
		/// Get the currently set Blue value (0-255)
		/// </summary>
		Uint8 getBlue() const { return blue; };

		/// <summary>
		/// Get the currently set Alpha value (0-255)
		/// </summary>
		Uint8 getAlpha() const { return alpha; };
	private:
		void storeColors(double r, double g, double b, double a);
		void changeColor() const;
		Uint8 red;
		Uint8 green;
		Uint8 blue;
		Uint8 alpha;
	};

	extern Graphics graphics;
}

#endif
