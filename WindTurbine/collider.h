#ifndef COLLIDER_H
#define COLLIDER_H
#include <iostream>
#include <functional>

#include "poly_points.h"
#include "entity.h"

namespace wind {

	enum Shape {base, circle, rectangle, polygon };
	class PhysicsWorld; // Is this forward declaration?
	class RectangleCollider;

	class Collider{
	typedef std::function<void(Collider* coll_a, Collider* coll_b)> Callback;
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

		/// <summary>
		/// Used to pass a function that will be stored and used by the "onCollide"-callback function.
		/// </summary>
		/// <param name="call_back"> = A function of return type 'void' with two parameters: pointers to the colliders that triggered the callback.</param>
		void setOnCollide(std::function<void(Collider* coll_a, Collider* coll_b)> call_back);

		/// <summary>
		/// Set the Entity that this collider belongs to, can be used to resolve collisions in the collision callback-function.
		/// </summary>
		/// <param name="entity"> = Pointer to the entity</param>
		void setEntity(Entity* entity);

		/// <summary>
		/// Get a pointer to the Entity which this collider belongs to.
		/// </summary>
		/// <returns> = Pointer to the entity</returns>
		Entity* getEntity();

		/// <summary>
		/// Used to check if the collider is alive or if it should be removed from the physics world.
		/// </summary>
		/// <returns>True if the collider is alive, else false</returns>
		bool isAlive() {return alive;};

		/// <summary>
		/// Used to flag the collider for destruction, when called it will be removed by the physics world the next frame.
		/// </summary>
		void destroy() { alive = false; }
		
	protected:
		void onCollide(Collider* coll_a, Collider* coll_b) const;
		Entity* connectedEntity;

		static void emptyCallback(Collider* coll_a, Collider* coll_b) {};

		virtual void move();
		virtual void rotateVertices(double dt) {};

		Collider(PhysicsWorld* world, double x, double y, int radius); 
		Collider(const Collider& other) = delete;
		const Collider& operator=(const Collider& other) = delete;

		void validateNextX(double dt);
		void validateNextY(double dt);

		virtual bool validateNextPosition() = 0;
		bool toBoundry(Collider* circle) const;
		PhysicsWorld* world;
		Shape shape;

		std::function<void(Collider* coll_a, Collider* coll_b)> callBack;

		bool alive = true;
		double radius;
		double yPos;
		double xPos;
		double centerX;
		double centerY;
		double nextX;
		double nextY;
		double angle = 0;
		double xVel = 0;
		double yVel = 0;
		double rVel = 0;
	};
}
#endif
