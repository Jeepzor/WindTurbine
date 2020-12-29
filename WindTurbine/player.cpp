#include "player.h"

Player::Player() {
	xPos = 30;
	yPos = 40;
	yVel = 0;
	xVel = 0;
	dir = 0;
	maxSpeed = 300.0;
	acceleration = 4000.0;
	friction = 2000;
	sprite = new wind::Animation("../assets/run.png", 6, 0.09);
}

void Player::update(double dt) {
	sprite->update(dt);
	move(dt);
	applyVelocity(dt);
	applyFriction(dt);
	updateDirection();
}

void Player::move(double dt) {
	if (wind::turbine.keyDown("D")) {
		xVel = std::min(xVel + acceleration * dt, maxSpeed);
	}
	
	if (wind::turbine.keyDown("A")) {
		xVel = std::max(xVel - acceleration * dt, -maxSpeed);
	}
	
	if (wind::turbine.keyDown("S")) {
		yVel = std::min(yVel + acceleration * dt, maxSpeed);
	}
	
	if (wind::turbine.keyDown("W")) {
		yVel = std::max(yVel - acceleration * dt, -maxSpeed);
	}
	if (wind::turbine.keyDown("R")) {
		dir = dir + 1;
		sprite->setAngle(dir);
	}
}

void Player::applyVelocity(double dt) {
	xPos = xPos + xVel * dt;
	yPos = yPos + yVel * dt;
}

void Player::applyFriction(double dt) {
	if (xVel > 0) {
		xVel = std::max(xVel - friction * dt, 0.0);
	}
	else if (xVel < 0) {
		xVel = std::min(xVel + friction * dt, 0.0);
	}
	
	if (yVel > 0) {
		yVel = std::max(yVel - friction * dt, 0.0);
	}
	else if (yVel < 0) {
		yVel = std::min(yVel + friction * dt, 0.0);
	}
}

void Player::updateDirection() {
	if (xVel < 0) {
		sprite->setFlip(true, false);
	}else if (xVel > 0) {
		sprite->setFlip(false, false);
	}
}

void Player::draw() {
	sprite->draw(xPos, yPos);
}