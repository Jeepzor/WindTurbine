#include "collider.h"
#include "physics_world.h"
#include "rectangle_collider.h"
#include "graphics.h"

namespace wind {
	
	Collider::Collider(PhysicsWorld* physics_world, double x, double y, int circle_radius) {
		shape = base;
		world = physics_world;
		radius = circle_radius;
		xPos = x;
		yPos = y;
		xVel = 0;
		yVel = 0;
		nextX = x;
		nextY = y;

		physics_world->addObject(this);
	}

	void Collider::setVelocity(double x, double y) {
		xVel = x;
		yVel = y;
	}

	void Collider::update(double dt) {
		validateNextX(dt);
		validateNextY(dt);
		move();
	}

	void Collider::validateNextX(double dt) {
		nextX = xPos + xVel * dt;
		if (!validateNextPosition()) {
			nextX = xPos;
		}
	}

	void Collider::validateNextY(double dt) {
		nextY = yPos + yVel * dt;
		if (!validateNextPosition()) {
			nextY = yPos;
		}
	}

	void Collider::move() {
		xPos = nextX;
		yPos = nextY;
	}

	double Collider::getX() const {
		return xPos;
	}

	double Collider::getY() const {
		return yPos;
	}
	
	double Collider::getNextX() const {
		return nextX;
	}

	double Collider::getNextY() const {
		return nextY;
	}
	
	int Collider::getRadius() const {
		return radius;
	}

	Shape Collider::getShape() const {
		return shape;
	}
}
