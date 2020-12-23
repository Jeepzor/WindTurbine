#ifndef IMAGE_H
#define IMAGE_H
#include <SDL_image.h>
#include <string>

class Image {
public:
	Image(std::string path);
	Image(const Image& source);
	Image& operator = (const Image& source);
	Image();
	~Image();

	void draw(int, int);
	void setPosition(int, int);

	int getWidth();
	int getHeight();

	SDL_Texture* getAsset();

private:
	SDL_Surface* surface;
	SDL_Rect destination;
	SDL_Texture* asset;
	int width;
	int height;
	std::string assetPath;
};

#endif