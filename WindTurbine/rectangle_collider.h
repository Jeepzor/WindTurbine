#ifndef RECTANGLE_COLLIDER_H
#define RECTANGLE_COLLIDER_H

#include <string>
#include "physics_world.h"

namespace wind {
	class Collider;

	class RectangleCollider : public wind::Collider {
	public:
		RectangleCollider(PhysicsWorld* physics_world, double x, double y, double width, double height);
		int getWidth();
		int getHeight();
	private:
		bool validateNextPosition() override;
		bool toCircle(Collider* circle);
		bool aabb(RectangleCollider* rectangle);
		int width;
		int height;
		void draw();
	};

}
#endif