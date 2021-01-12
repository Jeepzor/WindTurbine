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

		/// <summary>
		/// Used to instantiate new PolygonColliders
		/// </summary>
		/// <param name="physics_world">Pointer to the PhysicsWorld that the body will inhabit.</param>
		/// <param name="x"> = Position on the X-axis</param>
		/// <param name="y"> = Position on the Y-axis</param>
		/// <param name="poly_points">PolyPoints Object which contains between 2-8 sets of X and Y coordinates</param>
		/// <returns>Pointer to a new PolygonCollider* instance.</returns>
		static PolygonCollider* getInstance(PhysicsWorld* physics_world, double x, double y, PolyPoints poly_points) {
			return new PolygonCollider(physics_world, x, y, poly_points);
		}

		~PolygonCollider()override;

		/// <summary>
		/// Returns a Vector of Vec2 (each containing a set of X and Y coordinates)
		/// </summary>
		/// <returns>Vector<Vec2></returns>
		std::vector< wind::Vec2> getVertices() const;

		/// <summary>
		/// Sets the rotation of the PolygonCollider in Radians
		/// </summary>
		/// <param name="amount"> = Radians</param>
		void setRotation(double amount) override;


	protected: 
		void rotateVertices(double dt) override;
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
