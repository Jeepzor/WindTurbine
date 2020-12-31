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
		if (validateNextPosition(dt)) {
			move();
		}
		else {
			//Collision callback function trigger.
		}
	}
	
	bool Collider::validateNextPosition(double dt) {
		nextX = xPos + xVel * dt;
		nextY = yPos + yVel * dt;
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
					if (circleToRectangle(this, other_object)) {
						legal = false;
					}
				}
				else if ((shape == "rectangle" && other_object->shape == "circle")) {
					if (circleToRectangle(other_object, this)) {
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
	
	bool Collider::aabb(Collider* other) { //Axis Alligned Bounding Box
		if (nextX + width > other->xPos && nextX < other->xPos + other->width && nextY + height > other->yPos && nextY < other->yPos + other->height) {
			return true;
		}else {
			return false;
		}
	}
	
	//Is the distance between the two circles less than their combined raidus?
	bool Collider::circleToCircle(Collider* other) {
		double dx = xPos - other->xPos;
		double dy = yPos - other->yPos;
		double distance = sqrt(dx * dx + dy * dy);
		double combined_radius = radius + other->radius;
		if (distance < combined_radius) {
			return true;
		}else {
			return false;
		}
	}
	

	bool Collider::circleToRectangle(Collider* circle, Collider* rectangle) {
		double rx = circle->xPos;
		double ry = circle->yPos;
		if (circle->xPos < rectangle->xPos) {
			rx = rectangle->xPos;
		}else if (circle->xPos > rectangle->xPos + rectangle->width){
			rx = rectangle->xPos + rectangle->width;
		}
		
		if (circle->yPos < rectangle->yPos) {
			ry = rectangle->yPos;
		}
		else if (circle->yPos > rectangle->yPos + rectangle->height) {
			ry = rectangle->yPos + rectangle->height;
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
