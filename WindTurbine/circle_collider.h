#ifndef CIRCLE_COLLIDER_H
#define CIRCLE_COLLIDER_H

#include <string>
#include "physics_world.h"

namespace wind {
	class Collider;
	class PolygonCollider;

	class CircleCollider : public wind::Collider {
	public:
		CircleCollider(PhysicsWorld* physics_world, double x, double y, double radius);
		
	private:
		void draw() const override;
		bool validateNextPosition() const override;
		bool toRectangle(wind::RectangleCollider* rectangle) const;
		bool toPolygon(wind::PolygonCollider* polygon) const;
	};

}
#endif