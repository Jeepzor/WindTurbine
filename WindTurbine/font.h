#ifndef TEXT_H
#define TEXT_H

#include <SDL_ttf.h>
#include <SDL.h>

#include <string>
namespace wind {
	class Font
	{
	public:

		Font(std::string path, int size);
		~Font();

		/// <summary>
		/// Render text on the screen
		/// </summary>
		/// <param name="text"> = A string for the text that should be displayed</param>
		/// <param name="x"> = X position for the left side of the text</param>
		/// <param name="y"> = Y position for the top side of the text</param>
		void draw(std::string text, double x, double y);

		/// <summary>
		/// Render text (which can be rotated) on the screen
		/// </summary>
		/// <param name="text"> = A string for the text that should be displayed</param>
		/// <param name="x"> = X position for the left side of the text</param>
		/// <param name="y"> = Y position for the top side of the text</param>
		/// <param name="angle"> = Angle in Radians</param>
		void draw(std::string text, double x, double y, double angle);
		
		/// <summary>
		/// Get a pointer to the TTF_Font which is used
		/// </summary>
		TTF_Font* getFont() { return font; };
	private:
		SDL_Texture* texture = nullptr;
		SDL_Surface* surface = nullptr;
		SDL_Rect destination;
		TTF_Font* font;
		int size;
	};
}

#endif

