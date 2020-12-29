#include "physics_world.h"

namespace wind {
	PhysicsWorld::PhysicsWorld(double x_velocity, double y_velocity) {
		objects;
		xVel = x_velocity;
		yVel = y_velocity;
	}
	
	void PhysicsWorld::addObject(Collider* new_object) {
		objects.push_back(new_object);
	}
}
