#include "circle_collider.h"
#include "rectangle_collider.h"
#include "polygon_collider.h"
#include "graphics.h"
#include "vec2.h"
#include "math.h"

namespace wind {

	CircleCollider::CircleCollider(PhysicsWorld* physics_world, double x, double y, double radius) : wind::Collider::Collider(physics_world, x, y, radius) {
		shape = circle;
		centerX = 0;
		centerY = 0;
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

	bool CircleCollider::toPolygon(PolygonCollider* polygon) const {
		std::vector<wind::Vec2> ov = polygon->getVertices();
		for (int i = 0; i <= ov.size() - 1; i++)
		{
			double x1;
			double x2;
			double y1;
			double y2;

			if (wind::math.distance(ov[i].x + polygon->getX(), ov[i].y + polygon->getY(), getNextX(), getNextY()) < getRadius()) {
				return true;
			}

			if (i == ov.size() - 1) {
				x1 = ov[0].x + polygon->getX();
				x2 = ov[ov.size() - 1].x + polygon->getX();
				y1 = ov[0].y + polygon->getY();
				y2 = ov[ov.size() - 1].y + polygon->getY();
			}
			else {
				x1 = ov[i].x + polygon->getX();
				x2 = ov[i + 1].x + polygon->getX();
				y1 = ov[i].y + polygon->getY();
				y2 = ov[i + 1].y + polygon->getY();
			}
			double length_of_line = wind::math.distance(x1, y1, x2, y2);

			double distance1 = wind::math.distance(x1, y1, getNextX(), getNextY());
			double distance2 = wind::math.distance(x2, y2, getNextX(), getNextY());

			if (distance1 + distance2 >= length_of_line - getRadius() * 0.99 && distance1 + distance2 <= length_of_line + getRadius() * 0.99) {
				return true;
			}
		}
		return false;
	}

	bool CircleCollider::validateNextPosition() const {
		bool legal = true;
		for (auto other_collider : world->getColliders()) {
			if (this != other_collider) { // Don't collide with yourself

				if (shape == circle && other_collider->getShape() == circle) {
					CircleCollider* other_circle{ dynamic_cast<CircleCollider*>(other_collider) };
					if (toBoundry(other_circle)) {
						legal = false;
					}
				}
				else if ((shape == circle && other_collider->getShape() == rectangle)) {
					RectangleCollider* rectangle_collider{ dynamic_cast<RectangleCollider*>(other_collider) };
					if (toRectangle(rectangle_collider)) {
						legal = false;
					}
				}else if ((shape == circle && other_collider->getShape() == polygon)) {
					PolygonCollider* polygon_collider{ dynamic_cast<PolygonCollider*>(other_collider) };
					if (toPolygon(polygon_collider)) {
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