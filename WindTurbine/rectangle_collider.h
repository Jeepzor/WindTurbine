#ifndef RECTANGLE_COLLIDER_H
#define RECTANGLE_COLLIDER_H

#include <string>

#include "physics_world.h"
#include "point.h"
#include "collider.h"

namespace wind {
	class PolygonCollider;
	class CircleCollider;

	class RectangleCollider : public wind::Collider {
	public:
		~RectangleCollider()override;

		/// <summary>
		/// Used to instantiate new RectangleColliders
		/// </summary>
		/// <param name="physics_world"> = Pointer to the PhysicsWorld that the body will inhabit</param>
		/// <param name="x"> = Position on the X-axis</param>
		/// <param name="y"> = Position on the Y-axis</param>
		/// <param name="width"> = Width of the Rectangle</param>
		/// <param name="height"> = Height of the Rectangle</param>
		/// <returns>Pointer to a new RectangleCollider* instance</returns>
		static RectangleCollider* getInstance(PhysicsWorld* physics_world, double x, double y, double width, double height) { 
			return new RectangleCollider(physics_world, x, y, width, height); }

		/// <summary>
		/// Returns the width of the rectangle.
		/// </summary>
		/// <returns>int width</returns>
		int getWidth() const;

		/// <summary>
		/// Returns the height of the rectangle.
		/// </summary>
		/// <returns>int height</returns>
		int getHeight() const;

		/// <summary>
		/// Returns a Vector of Points (Which contains an X and Y position).
		/// </summary>
		/// <returns>Vector of Points></returns>
		std::vector<Point> getVertices() const;

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
		std::vector< wind::Point> vertices;
	};

} 
#endif