#include "physics_world.h"
#include "collider.h"

namespace wind {
	PhysicsWorld::PhysicsWorld(double x_velocity, double y_velocity) {
		objects;
		xVel = x_velocity;
		yVel = y_velocity;
	}
	
	void PhysicsWorld::addObject(Collider* new_object) {
		objects.push_back(new_object);
	}

	void PhysicsWorld::update(double dt) const {
		for (auto currrent_object : objects) {
			currrent_object->update(dt);
		}
	}
	
	void PhysicsWorld::draw() const {
		for (auto currrent_object : objects) {
			currrent_object->draw();
		}
	}

	std::vector<Collider*> PhysicsWorld::getObjects() const {
		return objects;
	}


}
