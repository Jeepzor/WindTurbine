#ifndef PHYSICS_WORLD_H
#define PHYSICS_WORLD_H

#include <vector>

#include "collider.h"

namespace wind {
	class PhysicsWorld {
	public:
		PhysicsWorld(double xVel, double yVel);
		void addObject(Collider* obj);
	private:
		std::vector<Collider*> objects;
		double yVel;
		double xVel;
	};

}
#endif
