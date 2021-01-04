#ifndef RECTANGLE_COLLIDER_H
#define RECTANGLE_COLLIDER_H

#include <string>
#include "physics_world.h"
#include "vec2.h"

namespace wind {
	class Collider;
	class PolygonCollider;
	class CircleCollider;

	class RectangleCollider : public wind::Collider {
	public:
		RectangleCollider(PhysicsWorld* physics_world, double x, double y, double width, double height);
		int getWidth() const;
		int getHeight() const;
		std::vector< wind::Vec2> getVertices() const;
	private:
		std::vector< wind::Vec2> vertices;
		bool validateNextPosition() const override;
		bool toCircle(Collider* circle) const;
		bool aabb(RectangleCollider* rectangle) const;
		bool toPolygon(PolygonCollider* other_polygon) const;
		int width;
		int height;
		void draw() const;
	};

} 
#endif