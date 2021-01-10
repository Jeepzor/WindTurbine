#include <string>
#include "player.h"

Player::Player(wind::PhysicsWorld* world) {
	xPos = 300;
	yPos = 40;
	yVel = 0;
	xVel = 0;
	dir = 0;
	maxSpeed = 300.0;
	acceleration = 4000.0;
	friction = 2000;
	collider = wind::CircleCollider::getInstance(world,xPos, yPos, 30);
	sprite = new wind::Animation("../assets/run.png", 6, 0.09);
}

void Player::update(double dt) {
	sprite->update(dt);
	move(dt);
	applyVelocity();
	syncPosition();
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

void Player::applyVelocity() {
	collider->setVelocity(xVel, yVel);
}

void Player::syncPosition() {
	xPos = collider->getX() - 50;
	yPos = collider->getY() - 50;
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
	//wind::graphics.line(xPos + 50, yPos + 50, wind::turbine.getMouseX(), wind::turbine.getMouseY());
}