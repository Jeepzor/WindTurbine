#include "circle_collider.h"
#include "rectangle_collider.h"
#include "graphics.h"

namespace wind {

	CircleCollider::CircleCollider(PhysicsWorld* physics_world, double x, double y, double radius) : wind::Collider::Collider(physics_world, x, y, radius) {
		shape = circle;
	}

	//Is the distance between the two circles less than their combined raidus?
	bool CircleCollider::toCircle(CircleCollider* other) const {
		double dx = nextX - other->xPos;
		double dy = nextY - other->yPos;
		double distance = sqrt(dx * dx + dy * dy);
		double combined_radius = radius + other->radius;
		if (distance < combined_radius) {
			return true;
		}
		else {
			return false;
		}
	}

	bool CircleCollider::toRectangle(RectangleCollider* rectangle) const {
		double rx = nextX;
		double ry = nextY;
		if (nextX < rectangle->getX()) {
			rx = rectangle->getX();
		}
		else if (nextX > rectangle->getX() + rectangle->getWidth()) {
			rx = rectangle->getX() + rectangle->getWidth();
		}

		if (nextY < rectangle->getY()) {
			ry = rectangle->getY();
		}
		else if (nextY > rectangle->getY() + rectangle->getHeight()) {
			ry = rectangle->getY() + rectangle->getHeight();
		}

		double distanceX = nextX - rx;
		double distanceY = nextY - ry;
		double distance = sqrt(distanceX * distanceX + distanceY * distanceY);

		if (distance < radius) {
			return true;
		}
		else {
			return false;
		}
	}

	bool CircleCollider::validateNextPosition() const {
		bool legal = true;
		for (auto other_collider : world->getColliders()) { // TODO -> Dont check objects that are not moving!
			if (this != other_collider) { // Don't collide with yourself

				if (shape == circle && other_collider->getShape() == circle) {
					CircleCollider* other_circle{ dynamic_cast<CircleCollider*>(other_collider) };
					if (toCircle(other_circle)) {
						legal = false;
					}
				}
				else if ((shape == circle && other_collider->getShape() == rectangle)) {
					RectangleCollider* rectangle_object{ dynamic_cast<RectangleCollider*>(other_collider) };
					if (toRectangle(rectangle_object)) {
						legal = false;
					}
				}
			}
		}
		return legal;
	}

	void CircleCollider::draw() const {
		graphics.circle("line", xPos, yPos, radius);
	}
}