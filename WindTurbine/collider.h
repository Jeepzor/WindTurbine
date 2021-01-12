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
		virtual ~Collider()= 0 {};

		/// <summary>
		/// Updates the collider.
		/// </summary>
		/// <param name="dt"> = Delta Time</param>
		virtual void update(double dt);

		/// <summary>
		/// Draws the collider
		/// </summary>
		virtual void draw() const = 0;

		/// <summary>
		/// Set the velocity of the collider, in pixels per second.
		/// </summary>
		/// <param name="x"> = X-velocity</param>
		/// <param name="y"> = Y-velocity</param>
		virtual void setVelocity(double x, double y);

		/// <summary>
		/// Sets the rotation of the collider (Only affects Polygons).
		/// </summary>
		/// <param name="amount"></param>
		virtual void setRotation(double amount) {};

		/// <summary>
		/// Get the X position of the collider.
		/// </summary>
		/// <returns>double X</returns>
		double getX() const;

		/// <summary>
		/// Get the Y position of the collider.
		/// </summary>
		/// <returns>double Y</returns>
		double getY() const;

		/// <summary>
		/// Get X position of the center of the collider.
		/// </summary>
		/// <returns>double X</returns>
		double getCenterX() const;

		/// <summary>
		/// Get Y position of the center of the collider.
		/// </summary>
		/// <returns>double Y</returns>
		double getCenterY() const;

		/// <summary>
		/// Get the theoretical next position of the collider on the X-axis.
		/// </summary>
		/// <returns>double X</returns>
		double getNextX() const;

		/// <summary>
		/// Get the theoretical next position of the collider on the Y-axis.
		/// </summary>
		/// <returns>double Y</returns>
		double getNextY() const;

		/// <summary>
		/// Return the radius of the shape, every shape has a radius in order to do a less costly collision detection algorithm first, before checking more exact and expensive ones.
		/// </summary>
		/// <returns>double X</returns>
		int getRadius() const;

		/// <summary>
		/// Gets the shape of the collider.
		/// </summary>
		/// <returns>Enum Shape</returns>
		Shape getShape() const;
		
	protected:
		virtual void move();
		virtual void rotateVertices(double dt) {};

		Collider(PhysicsWorld* world, double x, double y, int radius); 
		Collider(const Collider& other) = delete;
		const Collider& operator=(const Collider& other) = delete;

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
