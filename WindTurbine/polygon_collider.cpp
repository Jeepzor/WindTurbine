#include "polygon_collider.h"
#include "circle_collider.h"
#include "rectangle_collider.h"
#include "graphics.h"
#include "vec2.h"

namespace wind {

	PolygonCollider::PolygonCollider(PhysicsWorld* physics_world, double x, double y, std::vector<wind::Vec2> poly_points) : wind::Collider::Collider(physics_world, x, y, 0) {
		shape = polygon;
		vertices = poly_points;
	}

	bool PolygonCollider::validateNextPosition() const {
		bool legal = true;
		for (auto other_collider : world->getColliders()) {
			if (this != other_collider) { // Don't collide with yourself
			
				if (shape == polygon && other_collider->getShape() == polygon) {
					PolygonCollider* other_polygon{ dynamic_cast<PolygonCollider*>(other_collider) };
					if (toPolygon(other_polygon)) {
						legal = false;
					}
				}
				/*
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
		graphics.line(vertices[0].x + xPos, vertices[0].y + yPos, vertices[vertices.size() - 1].x + xPos, vertices[vertices.size() - 1].y + yPos);
		for (int i = 0; i < vertices.size() - 1; i++)
		{
			graphics.line(vertices[i].x + xPos, vertices[i].y + yPos, vertices[i + 1].x + xPos, vertices[i + 1].y + yPos);
		};
	}

	std::vector<wind::Vec2> PolygonCollider::getVertices() const {
		return vertices;
	}

	bool PolygonCollider::toPolygon(PolygonCollider* other_polygon) const {
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

			for (int j = 0; j <= other_polygon->vertices.size() - 1; j++) {
				if (j == other_polygon->vertices.size() - 1) {
					double x3 = ov[0].x + other_polygon->getX();
					double x4 = ov[other_polygon->vertices.size() - 1].x + other_polygon->getX();
					double y3 = ov[0].y + other_polygon->getY();
					double y4 = ov[other_polygon->vertices.size() - 1].y + other_polygon->getY();

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
}

/*
* Poly -> Square
* Poly -> Circle
* "First circle check"
* "Squeeze past"
* Rotation ?
* "Square polys"
*/