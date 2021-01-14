#ifndef PHYSICS_WORLD_H
#define PHYSICS_WORLD_H

#include <vector>
#include "collider.h"

namespace wind {
	class PhysicsWorld {
	public:
		PhysicsWorld(double xVel, double yVel);
		void addObject(Collider* obj);
		void update(double dt);
		void draw() const;
		void toggleDebug() { debug = !debug; };
		std::vector<Collider*> getColliders() const;
	private:
		void removeDead();
		std::vector<Collider*> colliders;
		double yVel;
		double xVel;
		bool debug = false;
	};
}

#endif
