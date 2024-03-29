#include "circle_collider.h"
#include "rectangle_collider.h"
#include "polygon_collider.h"
#include "graphics.h"
#include "point.h"
#include "math.h"

namespace wind {

	CircleCollider::CircleCollider(PhysicsWorld* physics_world, double x, double y, double radius) : wind::Collider::Collider(physics_world, x, y, radius) {
		shape = circle;
		centerX = 0;
		centerY = 0;
	}

	CircleCollider::~CircleCollider() {

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

		double distance = math.distance(nextX, nextY, rx, ry);

		if (distance < radius) {
			return true;
		}
		else {
			return false;
		}
	}

	bool CircleCollider::toPolygon(PolygonCollider* polygon) const {
		std::vector<wind::Point> ov = polygon->getVertices();
		for (unsigned int i = 0; i <= ov.size() - 1; i++)
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

			double distance_x = x1 - x2;
			double distance_y = y1 - y2;
			double line_length = sqrt((distance_x * distance_x) + (distance_y * distance_y));

			double dot_product = (((getNextX() - x1) * (x2 - x1)) + ((getNextY() - y1) * (y2 - y1))) / pow(line_length, 2);

			double min_x = x1 + (dot_product * (x2 - x1));
			double min_y = y1 + (dot_product * (y2 - y1));

			if (math.pointInLine(x1, y1, x2, y2, min_x, min_y)) {
				double distance = math.distance(min_x, min_y, getNextX(), getNextY());
				if (distance <= getRadius()) {
					return true;
				}
			}
		}
		return false;
	}

	bool CircleCollider::validateNextPosition(int normal_x, int normal_y) {
		bool legal = true;
		for (auto other_smart_collider : world->getColliders()) {
			auto other_collider = other_smart_collider.get();

			// Ignore collision if:
			//Other collider is this collider
			//Other collider is of the same filterGroup
			//Other collider is a sensor
			if (this != other_collider && this->differentFilterGroup(other_collider->getFilterGroup()) && !other_collider->isSensor() ) { 
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

					if (!legal)  {
						nx += normal_x;
						ny += normal_y;
						onCollide(this, other_collider);
					}
				}
			}
		}
		return legal;
	}

	void CircleCollider::draw() const {
		graphics.circle("line", xPos, yPos, static_cast<int>(radius));
	}
}