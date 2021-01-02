#ifndef CIRCLE_COLLIDER_H
#define CIRCLE_COLLIDER_H

#include <string>
#include "physics_world.h"

namespace wind {
	class Collider;

	class CircleCollider : public wind::Collider {
	public:
		CircleCollider(PhysicsWorld* physics_world, double x, double y, double radius);
		
	private:
		void draw() override;
		bool validateNextPosition() override;
		bool toCircle(CircleCollider* circle);
		bool toRectangle(wind::RectangleCollider* rectangle);
	};

}
#endif