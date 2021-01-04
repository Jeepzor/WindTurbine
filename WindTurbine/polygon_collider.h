#ifndef POLYGON_COLLIDER_H
#define POLYGON_COLLIDER_H

#include <string>
#include "physics_world.h"
#include "vec2.h"

namespace wind {
	class Collider;
	class CircleCollider;

	class PolygonCollider : public wind::Collider {
	public:
		PolygonCollider(PhysicsWorld* physics_world, double x, double y, std::vector<wind::Vec2> poly_points);
		std::vector< wind::Vec2> getVertices() const;
	private:
		void draw() const override;
		bool validateNextPosition() const override;
		bool toCircle(CircleCollider* circle) const;
		std::vector< wind::Vec2> vertices;
		bool polygonIntersect(std::vector<wind::Vec2> ov, double other_x, double other_y) const;
		bool toRectangle(RectangleCollider* other_rectangle) const;
		//bool toRectangle(wind::RectangleCollider* rectangle) const;
		bool toPolygon(wind::PolygonCollider* polygon) const;
	};

}
#endif
