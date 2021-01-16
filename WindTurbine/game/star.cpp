#include <string>
#include "star.h"

Star::Star(double x, double y) {
	xPos = x;
	yPos = y;
	
	asset = wind::Image::getInstance("game/assets/star.png");
	speed = 350 * wind::math.random() + 100;
	scale = speed / 400; // Tie the scale to the speed to create perception of depth
	asset->setScale(scale);
}

Star::~Star() {
	delete asset;
}


void Star::update(double dt) {
	yPos += speed * dt;
	if (yPos > 800) {
		yPos = -50;
	}
}


void Star::draw() {
	asset->draw(xPos, yPos);
}