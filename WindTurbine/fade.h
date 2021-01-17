#ifndef FADE_H
#define FADE_H
#include "wind_turbine.h"
namespace wind {
	class Fade
	{
	public:
		friend class Turbine;

		Fade() {};
		/// <summary>
		/// Fade the screen to black
		/// </summary>
		/// <param name="fade_duration"> = Speed of the fade</param>
		void out(double fade_duration);

		/// <summary>
		/// Fade away the black overlay, returning the game to normal.
		/// </summary>
		/// <param name="fade_duration"> = Speed of the fade</param>
		void in(double fade_duration);
	private:
		void update(double dt);
		void draw();
		double duration = 0;
		double targetAlpha = 0;
		double alpha = 0; // (0-255)
		double speed = 0;
	};
	extern Fade fade;
}

#endif