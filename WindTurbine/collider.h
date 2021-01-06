#ifndef COLLIDER_H
#define COLLIDER_H
#include "poly_points.h"
#include <iostream>

namespace wind {
	enum Shape {base, circle, rectangle, polygon };
	class PhysicsWorld; // Is this forward declaration?
	class RectangleCollider;

	class Collider{
	public:
		Collider(PhysicsWorld* world, double x, double y, int radius); // for circle, break out into class later.
		virtual ~Collider() {}
		virtual void update(double dt);
		virtual void draw() const = 0;
		virtual void move();
		virtual void setVelocity(double x, double y);
		virtual void rotateVertices(double dt) {};
		virtual void setRotation(double amount) {};
		double getX() const;
		double getY() const;
		double getCenterX() const;
		double getCenterY() const;
		double getNextX() const;
		double getNextY() const;
		int getRadius() const;
		Shape getShape() const;
		
	protected:
		virtual bool validateNextPosition() const = 0;
		void validateNextX(double dt);
		void validateNextY(double dt);
		bool toBoundry(Collider* circle) const;
		 
		PhysicsWorld* world;
		Shape shape;
		double angle;
		double radius;
		double yPos;
		double xPos;
		double centerX;
		double centerY;
		double xVel;
		double yVel;
		double rVel;
		double nextX;
		double nextY;
	};

}
#endif
