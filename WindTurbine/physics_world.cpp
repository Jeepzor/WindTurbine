#include "physics_world.h"
#include "collider.h"

namespace wind {
	PhysicsWorld::PhysicsWorld(double x_velocity, double y_velocity) {
		colliders;
		xVel = x_velocity;
		yVel = y_velocity;
	}
	
	void PhysicsWorld::addObject(Collider* new_object) {
		colliders.push_back(new_object);
	}

	void PhysicsWorld::update(double dt) const {
		for (auto currrent_object : colliders) {
			currrent_object->update(dt);
		}
	}
	
	void PhysicsWorld::draw() const {
		for (auto currrent_object : colliders) {
			currrent_object->draw();
		}
	}

	std::vector<Collider*> PhysicsWorld::getColliders() const {
		return colliders;
	}


}
