#ifndef RECTANGLE_COLLIDER_H
#define RECTANGLE_COLLIDER_H

#include <string>
#include "physics_world.h"

namespace wind {
	class Collider;

	class RectangleCollider : public wind::Collider {
	public:
		RectangleCollider(PhysicsWorld* physics_world, double x, double y, double width, double height);
		int getWidth() const;
		int getHeight() const;
	private:
		bool validateNextPosition() const override;
		bool toCircle(Collider* circle) const;
		bool aabb(RectangleCollider* rectangle) const;
		int width;
		int height;
		void draw() const;
	};

}
#endif