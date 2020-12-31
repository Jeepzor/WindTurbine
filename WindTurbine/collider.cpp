#include "collider.h"
#include "physics_world.h"
#include "graphics.h"

namespace wind {
	Collider::Collider(PhysicsWorld* physics_world, double x, double y, int collider_width, int collider_height) {
		shape = "rectangle";
		world = physics_world;
		width = collider_width;
		height = collider_height;
		radius = 0;
		xPos = x;
		yPos = y;
		xVel = 0;
		yVel = 0;
		nextX = x;
		nextY = y;
		world->addObject(this);
	}
	
	Collider::Collider(PhysicsWorld* physics_world, double x, double y, int circle_radius) {
		shape = "circle";
		world = physics_world;
		width = 0;
		height = 0;
		radius = circle_radius;
		xPos = x;
		yPos = y;
		xVel = 0;
		yVel = 0;
		nextX = x;
		nextY = y;
		world->addObject(this);
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
	
	bool Collider::validateNextPosition() {
		bool legal = true;
		for (auto other_object : world->getObjects()) { // TODO -> Dont check objects that are not moving!
			if (this != other_object) { // Don't collide with yourself
				if (shape == "rectangle" && other_object->shape == "rectangle") {
					if (aabb(other_object)) {
						legal = false;
					}
				}
				else if (shape == "circle" && other_object->shape == "circle") {
					if (circleToCircle(other_object)) {
						legal = false;
					}
				}
				else if ((shape == "circle" && other_object->shape == "rectangle")) {
					if (circleToRectangle(other_object)) {
						legal = false;
					}
				}
				else if ((shape == "rectangle" && other_object->shape == "circle")) {
					if (rectangleToCircle(other_object)) {
						legal = false;
					}
				}
			}
		}

		return legal;
	}

	void Collider::move() {
		xPos = nextX;
		yPos = nextY;
	}

	double Collider::getX() {
		return xPos;
	}

	double Collider::getY() {
		return yPos;
	}
	
	bool Collider::aabb(Collider* other) { //Axis Alligned Bounding Box
		if (nextX + width > other->xPos && nextX < other->xPos + other->width && nextY + height > other->yPos && nextY < other->yPos + other->height) {
			return true;
		}else {
			return false;
		}
	}
	
	//Is the distance between the two circles less than their combined raidus?
	bool Collider::circleToCircle(Collider* other) {
		double dx = nextX - other->xPos;
		double dy = nextY - other->yPos;
		double distance = sqrt(dx * dx + dy * dy);
		double combined_radius = radius + other->radius;
		if (distance < combined_radius) {
			return true;
		}else {
			return false;
		}
	}
	

	bool Collider::circleToRectangle(Collider* rectangle) {
		double rx = nextX;
		double ry = nextY;
		if (nextX < rectangle->xPos) {
			rx = rectangle->xPos;
		}else if (nextX > rectangle->xPos + rectangle->width){
			rx = rectangle->xPos + rectangle->width;
		}
		
		if (nextY < rectangle->yPos) {
			ry = rectangle->yPos;
		}
		else if (nextY > rectangle->yPos + rectangle->height) {
			ry = rectangle->yPos + rectangle->height;
		}

		double distanceX = nextX - rx;
		double distanceY = nextY - ry;
		double distance = sqrt(distanceX * distanceX + distanceY * distanceY);

		if (distance < radius) {
			return true;
		}
		else {
			return false;
		}
	}

	bool Collider::rectangleToCircle(Collider* circle) {
		double rx = circle->xPos;
		double ry = circle->yPos;
		if (circle->xPos < xPos) {
			rx = xPos;
		}
		else if (circle->xPos > xPos + width) {
			rx = xPos + width;
		}

		if (circle->yPos < yPos) {
			ry = yPos;
		}
		else if (circle->yPos > yPos + height) {
			ry = yPos + height;
		}

		double distanceX = circle->xPos - rx;
		double distanceY = circle->yPos - ry;
		double distance = sqrt(distanceX * distanceX + distanceY * distanceY);

		if (distance < circle->radius) {
			return true;
		}
		else {
			return false;
		}
	}

	void Collider::draw() {
		if (shape == "rectangle") {
			graphics.rectangle("line", xPos, yPos, width, height);
		}
		else if (shape == "circle") {
			graphics.circle("line", xPos, yPos, radius);
		}
	}

}
