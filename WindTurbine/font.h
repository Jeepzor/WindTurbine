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
		void draw(std::string text, double x, double y);
		void draw(std::string text, double x, double y, double angle);
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

