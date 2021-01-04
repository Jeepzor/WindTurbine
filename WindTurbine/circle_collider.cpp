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

			double distX = x1 - x2;
			double distY = y1 - y2;
			double len = sqrt((distX * distX) + (distY * distY));

			double dot = (((getNextX() - x1) * (x2 - x1)) + ((getNextY() - y1) * (y2 - y1))) / pow(len, 2);

			double closestX = x1 + (dot * (x2 - x1));
			double closestY = y1 + (dot * (y2 - y1));

			bool onSegment = math.linePoint(x1, y1, x2, y2, closestX, closestY);
			if (onSegment) {
				// get distance to closest point
				distX = closestX - (getNextX());
				distY = closestY - (getNextY());
				double distance = sqrt((distX * distX) + (distY * distY));
				if (distance <= getRadius()) {
					return true;
				}
			}
		}
		return false;
	}

	bool CircleCollider::validateNextPosition() const {
		bool legal = true;
		for (auto other_collider : world->getColliders()) {
			if (this != other_collider) { // Don't collide with yourself
				if (toBoundry(other_collider)) { // Is the shape near enough to warrant more expensive calculations?
					if (other_collider->getShape() == circle) {
						CircleCollider* other_circle{ dynamic_cast<CircleCollider*>(other_collider) };
						if (toBoundry(other_circle)) {
							legal = false;
						}
					}
					else if ((other_collider->getShape() == rectangle)) {
						RectangleCollider* rectangle_collider{ dynamic_cast<RectangleCollider*>(other_collider) };
						if (toRectangle(rectangle_collider)) {
							legal = false;
						}
					}
					else if ((other_collider->getShape() == polygon)) {
						PolygonCollider* polygon_collider{ dynamic_cast<PolygonCollider*>(other_collider) };
						if (toPolygon(polygon_collider)) {
							legal = false;
						}
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