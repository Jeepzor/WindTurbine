#ifndef COLLIDER_H
#define COLLIDER_H

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

		double getX() const;
		double getY() const;
		int getRadius() const;
		Shape getShape() const;
		
	protected:
		virtual bool validateNextPosition() const = 0;
		void validateNextX(double dt);
		void validateNextY(double dt);

		PhysicsWorld* world;
		Shape shape;
		double radius;
		double yPos;
		double xPos;
		double xVel;
		double yVel;
		double nextX;
		double nextY;
	};

}
#endif
