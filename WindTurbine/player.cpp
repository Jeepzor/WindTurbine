#include "player.h"

Player::Player() {
	xPos = 30;
	yPos = 40;
	sprite = wind::Image("../assets/player.png");
}

void Player::draw() {
	sprite.draw(xPos, yPos);
}