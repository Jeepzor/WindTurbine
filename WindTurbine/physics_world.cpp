#include "physics_world.h"
#include "collider.h"

#include<iostream>
#include<vector>
#include<algorithm>

namespace wind {
	PhysicsWorld::PhysicsWorld(double x_velocity, double y_velocity) {
		colliders;
		xVel = x_velocity;
		yVel = y_velocity;
	}
	
	void PhysicsWorld::addObject(Collider* new_object) {
		colliders.push_back(new_object);
	}

	void PhysicsWorld::update(double dt)  {
		removeDead();

		for (auto currrent_object : colliders) {
			currrent_object->update(dt);
		}
	}

	
	void PhysicsWorld::removeDead() {
		colliders.erase(std::remove_if(colliders.begin(), colliders.end(),
			[](Collider* i) { return !(i->isAlive()); }), colliders.end());
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
