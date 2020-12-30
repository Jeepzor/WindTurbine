#include "collider.h"
#include "physics_world.h"
#include "graphics.h"

namespace wind {
	Collider::Collider(PhysicsWorld* physics_world, double x, double y, int collider_width, int collider_height) {
		world = physics_world;
		width = collider_width;
		height = collider_height;
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
			std::cout << "Wooop diii fucking dooo";
		}
	}
	
	bool Collider::validateNextPosition(double dt) {
		nextX = xPos + xVel * dt;
		nextY = yPos + yVel * dt;
		bool legal = true;
		for (auto other_object : world->getObjects()) {
			if (aabb(other_object)) {
				legal = false;
			}
		}
		
		return legal;
	}
	
	void Collider::move() {
		xPos = nextX;
		yPos = nextY;
	}
	
	bool Collider::aabb(Collider* other) {
		if (this == other) {
			return false;
		}else { 
			if (nextX + width > other->xPos && nextX < other->xPos + other->width && nextY + height > other->yPos && nextY < other->yPos + other->height) {
				return true;
			}else {
				return false;
			}
		}
	}

	void Collider::draw() {
		graphics.rectangle("fill", xPos, yPos, width, height);
	}

}
