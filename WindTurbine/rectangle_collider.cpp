#include <math.h>

#include "physics_world.h"
#include "rectangle_collider.h"
#include "circle_collider.h"
#include "polygon_collider.h"
#include "graphics.h"

namespace wind {

	RectangleCollider::RectangleCollider(PhysicsWorld* physics_world, double x, double y, double rect_width, double rect_height) : wind::Collider::Collider(physics_world, x, y, 0) {
		width = rect_width;
		height = rect_height;
		radius = std::sqrt(width * width + height * height) / 2; // get the distance between two oposite corners. Used for the first pass of the faster circle to circle detection.
		centerX = xPos - (xPos + width / 2); //Calculates the relative offset to the center X
		centerY = yPos - (yPos + height / 2);//Calculates the relative offset to the center Y
		shape = rectangle;


		vertices.push_back(wind::Vec2(0, 0));
		vertices.push_back(wind::Vec2(width, 0));
		vertices.push_back(wind::Vec2(width, height));
		vertices.push_back(wind::Vec2(0, height));
	}

	std::vector<wind::Vec2> RectangleCollider::getVertices() const {
		return vertices;
	}

	bool RectangleCollider::validateNextPosition() const {
		bool legal = true;
		for (auto other_collider : world->getColliders()) {
			if (this != other_collider) { // Don't collide with yourself
				if (toBoundry(other_collider)) {
					if (other_collider->getShape() == rectangle) {
						RectangleCollider* rectangle_object{ dynamic_cast<RectangleCollider*>(other_collider) };
						if (aabb(rectangle_object)) {
							legal = false;
						}
						
					}
					else if (other_collider->getShape() == circle) {
						CircleCollider* other_circle{ dynamic_cast<CircleCollider*>(other_collider) };
						if (toCircle(other_circle)) {
							legal = false;
						}
					}else if (other_collider->getShape() == polygon) {
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

	bool RectangleCollider::toPolygon(PolygonCollider* other_polygon) const {
		std::vector<wind::Vec2> ov = other_polygon->getVertices();
		bool coll = false;
		for (int i = 0; i <= vertices.size() - 1; i++)
		{
			double x1;
			double x2;
			double y1;
			double y2;
			if (i == vertices.size() - 1) {
				x1 = vertices[0].x + getNextX();
				x2 = vertices[vertices.size() - 1].x + getNextX();
				y1 = vertices[0].y + getNextY();
				y2 = vertices[vertices.size() - 1].y + getNextY();
			}
			else {
				x1 = vertices[i].x + getNextX();
				x2 = vertices[i + 1].x + getNextX();
				y1 = vertices[i].y + getNextY();
				y2 = vertices[i + 1].y + getNextY();
			}

			for (int j = 0; j <= ov.size() - 1; j++) {
				if (j == ov.size() - 1) {
					double x3 = ov[0].x + other_polygon->getX();
					double x4 = ov[ov.size() - 1].x + other_polygon->getX();
					double y3 = ov[0].y + other_polygon->getY();
					double y4 = ov[ov.size() - 1].y + other_polygon->getY();

					double testA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
					double testB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
					if (testA >= 0 && testA <= 1 && testB >= 0 && testB <= 1) {
						coll = true;
					}
				}
				else {
					double x3 = ov[j].x + other_polygon->getX();
					double x4 = ov[j + 1].x + other_polygon->getX();
					double y3 = ov[j].y + other_polygon->getY();
					double y4 = ov[j + 1].y + other_polygon->getY();

					double testA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
					double testB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

					if (testA >= 0 && testA <= 1 && testB >= 0 && testB <= 1) {
						coll = true;
					}
				}
			}
		};
		return coll;
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