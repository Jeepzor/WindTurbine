#ifndef ENTITY_H
#define ENTITY_H
#include "wind_turbine.h"
#include "hibernate.h"

namespace wind {
	class Entity
	{
	public:
		virtual ~Entity() = 0;

		/// <summary>
		/// Render the entity to the window
		/// </summary>
		virtual void draw() {};

		/// <summary>
		/// Update the entity
		/// </summary>
		/// <param name="dt"> = Delta time</param>
		virtual void update(double dt) {};

		/// <summary>
		/// Return the X position of the Entity
		/// </summary>
		/// <returns>X Position</returns>
		virtual double getX() const { return xPos; };

		/// <summary>
		/// Return the Y position of the Entity
		/// </summary>
		/// <returns>Y Position</returns>
		virtual double getY() const { return yPos; };

		/// <summary>
		/// Returns false if the entity is not alive and should be cleaned up
		/// </summary>
		/// <returns>bool alive</returns>
		virtual bool isAlive() { return alive; };

		/// <summary>
		/// Flags the entity for removal
		/// </summary>
		virtual void destroy() { alive = false; };

	protected:
		Entity();

		double xPos;
		double yPos;
		bool alive = true;

	private:
		Entity(const Entity&) = delete;
		const Entity& operator=(const Entity&) = delete;
	};
}

#endif