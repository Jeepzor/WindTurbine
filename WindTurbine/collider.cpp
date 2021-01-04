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
		centerX = y;
		centerY = y;
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

	//Is the distance between the two boundry-circles less than their combined raidus?
	bool Collider::toBoundry(Collider* other) const {
		double dx = (nextX - centerX) - (other->xPos - other->getCenterX());
		double dy = (nextY - centerY) - (other->yPos - other->getCenterY());
		double distance = sqrt(dx * dx + dy * dy);
		double combined_radius = radius + other->getRadius();
		if (distance < combined_radius) {
			return true;
		}
		else {
			return false;
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
	
	double Collider::getCenterX() const {
		return centerX;
	}

	double Collider::getCenterY() const {
		return centerY;
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
