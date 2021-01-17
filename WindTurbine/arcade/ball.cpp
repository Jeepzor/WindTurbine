#include <string>
#include <iostream>
#include "ball.h"
#include "character.h"

Ball::Ball(wind::PhysicsWorld* world, double x, double y) {
	xPos = x;
	yPos = y;
	
	yVel = 0;
	xVel = 0;

	//Elasticity multiplier.
	elasticity = 0.7;

	friction = 70;
	collider = wind::CircleCollider::getInstance(world, xPos, yPos, 15);
	collider->setEntity(this);

	collider->setOnCollide([=](wind::Collider* A, wind::Collider* B) mutable {
		if (Character* character = dynamic_cast<Character*>(B->getEntity())) {
			setVelocity(character->getVelX() * 3, character->getVelY() * 3);
		}
		else {
			if (allowed) {
				allowed = false;
				wind::hibernate.it([=]() mutable {allowed = true;}, 0.3);
				if (A->getNormalX() == 0) {
					setVelocity(-xVel * elasticity, yVel * elasticity);
				}
				if (A->getNormalY() == 0) {
					setVelocity(xVel * elasticity, -yVel * elasticity);
				}
			}
		}
		}
	);

	asset = wind::Image::getInstance("arcade/assets/ball.png");
	asset->setScale(2);
	asset->getDimensions(width, height);
}

void Ball::update(double dt) {
	applyVelocity();
	syncPosition();
	applyFriction(dt);
}


void Ball::setVelocity(double x, double y) {
	xVel = x;
	yVel = y;
}

double Ball::getX() const {
	return collider->getX();
}

double Ball::getY() const {
	return collider->getY();
}

void Ball::applyVelocity() {
	collider->setVelocity(xVel, yVel);
}

void Ball::syncPosition() {
	xPos = collider->getX() - width;
	yPos = collider->getY() - height;
}

void Ball::applyFriction(double dt) {
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


void Ball::draw() {
	asset->draw(xPos, yPos);
}