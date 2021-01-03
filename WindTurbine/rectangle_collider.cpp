#include <math.h>

#include "physics_world.h"
#include "rectangle_collider.h"
#include "circle_collider.h"
#include "graphics.h"

namespace wind {

	RectangleCollider::RectangleCollider(PhysicsWorld* physics_world, double x, double y, double rect_width, double rect_height) : wind::Collider::Collider(physics_world, x, y, 0) {
		width = rect_width;
		height = rect_height;
		radius = std::sqrt(width * width + height * height) / 2; // get the distance between two oposite corners. Used for the first pass of the faster circle to circle detection.
		shape = rectangle;
	}

	bool RectangleCollider::validateNextPosition() const {
		bool legal = true;
		for (auto other_collider : world->getColliders()) {
			if (this != other_collider) { // Don't collide with yourself

				if (shape == rectangle && other_collider->getShape() == rectangle) {
					RectangleCollider* rectangle_object{ dynamic_cast<RectangleCollider*>(other_collider) };
					if (aabb(rectangle_object)) {
						legal = false;
					}
				}
				else if ((shape == rectangle && other_collider->getShape() == circle)) {
					CircleCollider* other_circle{ dynamic_cast<CircleCollider*>(other_collider) };
					if (toCircle(other_circle)) {
						legal = false;
					}
				}
			}
		}
		return legal;
	}

	bool RectangleCollider::toCircle(Collider* circle) const {
		double rx = circle->getX();
		double ry = circle->getY();
		if (circle->getX() < xPos) {
			rx = xPos;
		}
		else if (circle->getX() > xPos + width) {
			rx = xPos + width;
		}

		if (circle->getY() < yPos) {
			ry = yPos;
		}
		else if (circle->getY() > yPos + height) {
			ry = yPos + height;
		}

		double distanceX = circle->getX() - rx;
		double distanceY = circle->getY() - ry;
		double distance = sqrt(distanceX * distanceX + distanceY * distanceY);

		if (distance < circle->getRadius()) {
			return true;
		}
		else {
			return false;
		}
	}

	bool RectangleCollider::aabb(RectangleCollider* other) const { //Axis Alligned Bounding Box
		if (nextX + width > other->xPos && nextX < other->xPos + other->width && nextY + height > other->yPos && nextY < other->yPos + other->height) {
			return true;
		}
		else {
			return false;
		}
	}

	int RectangleCollider::getWidth() const {
		return width;
	}
	
	int RectangleCollider::getHeight() const {
		return height;
	}

	void RectangleCollider::draw() const {
		graphics.rectangle("line", xPos, yPos, width, height);
		graphics.circle("line", xPos + width / 2, yPos + height / 2, radius);
	}
}