#include <string>
#include "character.h"

Character::Character(wind::PhysicsWorld* world) {
	xPos = 800;
	yPos = 400;
	yVel = 0;
	xVel = 0;
	
	goingDown = true;
	isIdle = true;

	maxSpeed = 300.0;
	acceleration = 4000.0;
	friction = 2000;
	collider = wind::CircleCollider::getInstance(world, xPos, yPos, 10);
	runUp = wind::Animation::getInstance("arcade/assets/run_up.png", 8, 0.09);
	runDown = wind::Animation::getInstance("arcade/assets/run_down.png", 8, 0.09);
	idleUp = wind::Animation::getInstance("arcade/assets/idle_up.png", 5, 0.1);
	idleDown = wind::Animation::getInstance("arcade/assets/idle_down.png", 5, 0.1);

	runUp->setScale(2);
	runDown->setScale(2);
	idleUp->setScale(2);
	idleDown->setScale(2);
}

void Character::update(double dt) {
	updateAnimation(dt);
	move(dt);
	applyVelocity();
	syncPosition();
	applyFriction(dt);
	updateDirection();
}

void Character::updateAnimation(double dt) {
	runUp->update(dt);
	runDown->update(dt);
	idleUp->update(dt);
	idleDown->update(dt);
}

void Character::move(double dt) {
	if (wind::turbine.keyDown("D")) {
		xVel = std::min(xVel + acceleration * dt, maxSpeed);
	}

	if (wind::turbine.keyDown("A")) {
		xVel = std::max(xVel - acceleration * dt, -maxSpeed);
	}

	if (wind::turbine.keyDown("W")) {
		goingDown = false;
		yVel = std::max(yVel - acceleration * dt, -maxSpeed);
	}

	if (wind::turbine.keyDown("S")) {
		goingDown = true;
		yVel = std::min(yVel + acceleration * dt, maxSpeed);
	}

	isIdle = false;
	if (xVel == 0 && yVel == 0) {
		isIdle = true;
	}
}

double Character::getX() {
	return collider->getX();
}

double Character::getY() {
	return collider->getY();
}

void Character::applyVelocity() {
	collider->setVelocity(xVel, yVel);
}

void Character::syncPosition() {
	xPos = collider->getX() - 70;
	yPos = collider->getY() - 105;
}

void Character::applyFriction(double dt) {
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

void Character::updateDirection() {
	if (xVel > 0) {
		runUp->setFlip(true, false);
		runDown->setFlip(true, false);
		idleUp->setFlip(true, false);
		idleDown->setFlip(true, false);
	}
	else if (xVel < 0) {
		runUp->setFlip(false, false);
		runDown->setFlip(false, false);
		idleUp->setFlip(false, false);
		idleDown->setFlip(false, false);
	}
}

void Character::draw() {
	if (isIdle) {
		if (goingDown) {
			idleDown->draw(xPos, yPos);
		}
		else  {
			idleUp->draw(xPos, yPos);
		}
	}
	else {
		if (goingDown) {
			runDown->draw(xPos, yPos);
		}
		else {
			runUp->draw(xPos, yPos);
		}
	}
}