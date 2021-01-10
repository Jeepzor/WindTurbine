#ifndef RECTANGLE_COLLIDER_H
#define RECTANGLE_COLLIDER_H

#include <string>

#include "physics_world.h"
#include "vec2.h"
#include "collider.h"

namespace wind {
	class PolygonCollider;
	class CircleCollider;

	class RectangleCollider : public wind::Collider {
	public:
		~RectangleCollider()override;

		static RectangleCollider* getInstance(PhysicsWorld* physics_world, double x, double y, double width, double height) { 
			return new RectangleCollider(physics_world, x, y, width, height); }

		int getWidth() const;
		int getHeight() const;

		std::vector< wind::Vec2> getVertices() const;

	protected:
		RectangleCollider(PhysicsWorld* physics_world, double x, double y, double width, double height);

	private:
		RectangleCollider(const RectangleCollider& other) = delete;
		const RectangleCollider& operator=(const RectangleCollider& other) = delete;

		void draw() const;

		int height;
		int width;

		bool validateNextPosition() const override;
		bool toCircle(Collider* circle) const;
		bool aabb(RectangleCollider* rectangle) const;
		bool toPolygon(PolygonCollider* other_polygon) const;
		std::vector< wind::Vec2> vertices;
	};

} 
#endif