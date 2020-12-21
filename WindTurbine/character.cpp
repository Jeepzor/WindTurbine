#include <string>
#include <iostream>
#include "Character.h"
#include "Image.h"

//Constructor
Character::Character(int x, int y, SDL_Renderer* renderer) {
	xPos = x;
	yPos = y;
	width = 30;
	height = 60;
	Image img = Image(renderer, "C:/Users/Jeeper/Desktop/University/CPROG/SDL Project/assets/player.png");

}


void Character::move(double x, double y, double dt) {
	xPos += x * dt;
	yPos += y * dt;
}

int Character::getX() {
	return static_cast<int>(xPos + 0.5); // + 0.5 because of auto truncation.
}

int Character::getY() {
	return static_cast<int>(yPos + 0.5); // + 0.5 because of auto truncation.
}

int Character::getWidth() {
	return width;
}

int Character::getHeight() {
	return height;
}
