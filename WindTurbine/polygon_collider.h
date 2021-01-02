#ifndef POLYGON_COLLIDER_H
#define POLYGON_COLLIDER_H

#include <string>
#include "physics_world.h"

namespace wind {
	class Collider;

	class PolygonCollider : public wind::Collider {
	public:
		PolygonCollider(PhysicsWorld* physics_world, double x, double y, std::vector< std::pair <int, int> >);

	private:
		void draw() const override;
		bool validateNextPosition() const override;
		//bool toCircle(CircleCollider* circle) const;
		//bool toRectangle(wind::RectangleCollider* rectangle) const;
	};

}
#endif
