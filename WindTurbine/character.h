#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include "image.h"

class Character {
public:
	Character(int x, int y, SDL_Renderer* renderer);
	void move(double x, double y, double dt);
	int getX();
	int getY();
	int getWidth();
	int getHeight();

private:
	SDL_Renderer* renderer;
	double xPos;
	double yPos;
	int width;
	int height;
	Image img;
};

#endif