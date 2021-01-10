#ifndef POLYGON_COLLIDER_H
#define POLYGON_COLLIDER_H

#include <string>

#include "physics_world.h"
#include "vec2.h"
#include "collider.h"

namespace wind {
	class CircleCollider;

	class PolygonCollider : public wind::Collider {
	public:
		static PolygonCollider* getInstance(PhysicsWorld* physics_world, double x, double y, PolyPoints poly_points) {
			return new PolygonCollider(physics_world, x, y, poly_points);
		}

		~PolygonCollider()override;

		std::vector< wind::Vec2> getVertices() const;

		void setRotation(double amount) override;
		void rotateVertices(double dt) override;

	protected: 
		PolygonCollider(PhysicsWorld* physics_world, double x, double y, PolyPoints poly_points);

	private:
		PolygonCollider(const PolygonCollider& other) = delete;

		const PolygonCollider& operator=(const PolygonCollider& other) = delete;

		void draw() const override;

		bool validateNextPosition() const override;
		bool toCircle(CircleCollider* circle) const;
		bool polygonIntersect(std::vector<wind::Vec2> ov, double other_x, double other_y) const;
		bool toRectangle(RectangleCollider* other_rectangle) const;
		bool toPolygon(wind::PolygonCollider* polygon) const;

		std::vector< wind::Vec2> vertices;
	};

}
#endif
