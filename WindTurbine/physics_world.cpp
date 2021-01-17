#include "physics_world.h"
#include "collider.h"

#include<iostream>
#include<vector>
#include<algorithm>

namespace wind {
	PhysicsWorld::PhysicsWorld(double x_velocity, double y_velocity) {
		xVel = x_velocity;
		yVel = y_velocity;
	}
	
	void PhysicsWorld::addObject(Collider* new_object) {
		std::shared_ptr<wind::Collider> smart_ptr(new_object);
		colliders.push_back(smart_ptr);
	}

	void PhysicsWorld::update(double dt)  {
		removeDead();

		for (auto &current_object : colliders) {
			if (current_object->isAlive()) {

				current_object->update(dt);
			}
		}
	}

	void PhysicsWorld::removeDead() {
		std::vector<std::shared_ptr<wind::Collider>>::iterator iter;
		for (iter = colliders.begin(); iter != colliders.end(); ) {
			if (!(*iter)->isAlive()) {
				iter = colliders.erase(iter);
			}
			else {
				++iter;
			}
		}
	}
	
	void PhysicsWorld::draw() const {
		if (debug) {
			for (auto &currrent_object : colliders) {
				currrent_object->draw();
			}
		}
	}

	std::vector<std::shared_ptr<wind::Collider>> PhysicsWorld::getColliders() const {
		return colliders;
	}


}
