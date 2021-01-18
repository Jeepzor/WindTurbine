#include "collider.h"
#include "physics_world.h"
#include "rectangle_collider.h"
#include "graphics.h"

namespace wind {
	Collider::Collider(PhysicsWorld* physics_world, double x, double y, double circle_radius) {
		shape = base;
		world = physics_world;
		radius = circle_radius;
		xPos = x;
		yPos = y;
		centerX = y;
		centerY = y;
		nextX = x;
		nextY = y;
		physics_world->addObject(this);
		setOnCollide(emptyCallback);
	}

	void Collider::setVelocity(double x, double y) {
		xVel = x;
		yVel = y;
	}

	void Collider::update(double dt) {
		if (!isStatic) {
			rotateVertices(dt);
			validateNextX(dt);
			validateNextY(dt);
			move();
			resetNormals();
		}
	}

	void Collider::resetNormals() {
		if (nx + ny > 0) {
			nx = 0;
			ny = 0;
		}
	}

	bool Collider::differentFilterGroup(int other) {
		if (filterGroup == 0) {
			return true;
		}
		else if (filterGroup == other) {
			return false;
		}
		else {
			return true;
		}
	}

	void Collider::validateNextX(double dt) {
		if (xVel == 0) return;
		nextX = xPos + (xVel + world->getGravityX()) * dt;
		if (!validateNextPosition(1, 0) && !isSensor() ) { // Sensors ignore collision
			nextX = xPos;
		}
	}

	void Collider::validateNextY(double dt) {
		if (yVel == 0) return;
		nextY = yPos + (yVel + world->getGravityY()) * dt;
		if (!validateNextPosition(0, 1) && !isSensor() ) { // Sensors ignore collisions.
			nextY = yPos;
		}
	}
	
	//Is the distance between the two boundry-circles less than their combined raidus?
	//Each shape is surrounded by a circle, in order to only check for more complex
	//collision detection if they are reasonably close.
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
		return static_cast<int>(radius);
	}

	Shape Collider::getShape() const {
		return shape;
	}	
	
	void Collider::setFilterGroup(int new_group) {
		filterGroup = new_group;
	}

	void Collider::setOnCollide(std::function<void(Collider* coll_a, Collider* coll_b)> call_back) {
		callBack = call_back;
	}
	
	void Collider::setEntity(Entity* entity) {
		connectedEntity = entity;
	}
	
	Entity* Collider::getEntity() {
		return connectedEntity;
	}
	
	void Collider::onCollide(Collider* coll_a, Collider* coll_b)const {
		callBack(coll_a, coll_b);
	}
}
