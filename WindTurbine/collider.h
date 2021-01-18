#ifndef COLLIDER_H
#define COLLIDER_H
#include <iostream>
#include <functional>

#include "poly_points.h"
#include "entity.h"

namespace wind {

	enum Shape {base, circle, rectangle, polygon };
	class PhysicsWorld;
	class RectangleCollider;
	class CircleCollider;

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
		/// Sets the rotation speed of the collider (Only affects Polygons).
		/// </summary>
		/// <param name="amount"> = Change in Radians per second</param>
		virtual void setRotation(double amount) {};

		/// <summary>
		/// Sets the rotation speed of the collider (Only affects Polygons).
		/// </summary>
		/// <param name="new_angle"> = Angle in Radians</param>
		virtual void setAngle(double new_angle) {};

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
		/// Check wether or not a collider is a sensor. Sensors trigger collision callbacks but don't react to them.
		/// </summary>
		/// <returns>True if it is a sensor and vice versa</returns>
		bool isSensor() { return sensor; };
		
		/// <summary>
		/// Use to set the collider to be a sensor. Sensors trigger collision callbacks but don't react to them.
		/// </summary>
		void setSensor() { sensor = true; };

		/// <summary>
		/// Used to flag the collider for destruction, when called it will be removed by the physics world the next frame.
		/// </summary>
		void destroy() { alive = false; }

		/// <summary>
		/// Collders that belong to the same filter group will ignore collisions with eachother
		/// </summary>
		/// <param name="new_filter"> = The group that this collider will belong to.</param>
		void setFilterGroup(int new_filter);

		/// <summary>
		/// Get the filter group that the collider belongs to
		/// </summary>
		/// <returns>Filter group</returns>
		int getFilterGroup() { return filterGroup; };

		/// <summary>
		/// Sets the collider to be unmovable and unaffected by gravity.
		/// </summary>
		void setStatic() { isStatic = true; };

		/// <summary>
		/// Sets the collider to be movable and affected by gravity.
		/// </summary>
		void setDynamic() { isStatic = false; };

		/// <summary>
		/// Get the normal X
		/// </summary>
		double getNormalX() { return nx; };

		/// <summary>
		/// Get the normal Y
		/// </summary>
		double getNormalY() { return ny; };
		
	protected:

		void resetNormals();
		void onCollide(Collider* coll_a, Collider* coll_b) const;
		Entity* connectedEntity;

		static void emptyCallback(Collider* coll_a, Collider* coll_b) {};

		virtual void move();
		virtual void rotateVertices(double dt) {};

		Collider(PhysicsWorld* world, double x, double y, double radius); 
		Collider(const Collider& other) = delete;
		const Collider& operator=(const Collider& other) = delete;

		void validateNextX(double dt);
		void validateNextY(double dt);

		bool differentFilterGroup(int other);

		virtual bool validateNextPosition(int nx, int ny) = 0;
		bool toBoundry(Collider* circle) const;
		PhysicsWorld* world;
		Shape shape;

		std::function<void(Collider* coll_a, Collider* coll_b)> callBack;

		double nx = 0;
		double ny = 0;
		int filterGroup = 0;
		bool isStatic = false;
		bool alive = true;
		bool sensor = false;
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
