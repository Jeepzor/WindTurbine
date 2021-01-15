#ifndef CIRCLE_COLLIDER_H
#define CIRCLE_COLLIDER_H

#include <string>
#include "physics_world.h"
#include "collider.h"
namespace wind {
	class PolygonCollider;

	class CircleCollider : public wind::Collider {
	public:

		/// <summary>
		/// Used to instantiate new CircleColliders
		/// </summary>
		/// <param name="physics_world"></param>
		/// <param name="x"> = Position on the X-axis</param>
		/// <param name="y"> = Position on the Y-axis</param>
		/// <param name="radius"> = Radius of the collider</param>
		/// <returns>Pointer to a new CircleCollider* instance</returns>
		static CircleCollider* getInstance(PhysicsWorld* physics_world, double x, double y, double radius) {
			return new CircleCollider(physics_world, x, y, radius);
		}

		~CircleCollider();
	protected:
		CircleCollider(PhysicsWorld* physics_world, double x, double y, double radius);
	private:
		CircleCollider(const CircleCollider& other) = delete;
		const CircleCollider& operator=(const CircleCollider& other) = delete;

		void draw() const override;

		bool validateNextPosition() override;
		bool toRectangle(wind::RectangleCollider* rectangle) const;
		bool toPolygon(wind::PolygonCollider* polygon) const;
	};

}
#endif