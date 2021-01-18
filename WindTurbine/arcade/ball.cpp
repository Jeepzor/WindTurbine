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
			if (A->getNormalX() == 1 && A->getNormalY() == 0) {
				setVelX(-xVel * elasticity);
			}
			if (A->getNormalY() == 1 && A->getNormalX() == 0) {
				setVelY(-yVel * elasticity);
			}
		}
	);

	asset = wind::Image::getInstance("arcade/assets/ball.png");
	asset->setScale(2);
	asset->getDimensions(width, height);
}

void Ball::update(double dt) {
	std::cout << xVel << "\n";
	rotation += xVel / 35 * dt;
	applyVelocity();
	syncPosition();
	applyFriction(dt);
	asset->setAngle(rotation);
}



void Ball::setVelX(double x) {
	xVel = x;
}

void Ball::setVelY(double y) {
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