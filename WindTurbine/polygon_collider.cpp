#include "polygon_collider.h"
#include "circle_collider.h"
#include "rectangle_collider.h"
#include "graphics.h"

namespace wind {

	PolygonCollider::PolygonCollider(PhysicsWorld* physics_world, double x, double y, std::vector< std::pair <int, int> >) : wind::Collider::Collider(physics_world, x, y, radius) {
		shape = circle;
	}

	

	bool PolygonCollider::validateNextPosition() const {
		bool legal = true;
		for (auto other_collider : world->getColliders()) { // TODO -> Dont check objects that are not moving!
			if (this != other_collider) { // Don't collide with yourself
			/*
				if (shape == polygon && other_collider->getShape() == rectangle) {
					RectangleCollider* other_rectangle{ dynamic_cast<RectangleCollider*>(other_collider) };
					if (toRectangle(other_rectangle)) {
						legal = false;
					}
				}
				else if ((shape == circle && other_collider->getShape() == rectangle)) {
					RectangleCollider* rectangle_object{ dynamic_cast<RectangleCollider*>(other_collider) };
					if (toRectangle(rectangle_object)) {
						legal = false;
					}
				}
		*/
			}
		}
		return legal;
	}

	void PolygonCollider::draw() const {
		graphics.circle("line", xPos, yPos, radius);
	}
}