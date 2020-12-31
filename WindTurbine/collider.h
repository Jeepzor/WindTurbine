#ifndef COLLIDER_H
#define COLLIDER_H

#include <iostream>

namespace wind {
	class PhysicsWorld; // Is this forward declaration?

	class Collider{
	public:
		Collider(PhysicsWorld* world, double x, double y, int width, int height);
		Collider(PhysicsWorld* world, double x, double y, int radius); // for circle, break out into class later.
		void update(double dt);
		void draw();
		void move();
		void setVelocity(double x, double y);
		bool validateNextPosition(double dt);
		bool aabb(Collider* other);
		bool circleToCircle(Collider* other);
		bool circleToRectangle(Collider* circle, Collider* rectangle);
	private:
		PhysicsWorld* world;
		std::string shape;
		int width;
		int height;
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
