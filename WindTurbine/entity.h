#ifndef ENTITY_H
#define ENTITY_H
#include "wind_turbine.h"

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
		virtual double getX() { return xPos; };

		/// <summary>
		/// Return the Y position of the Entity
		/// </summary>
		/// <returns>Y Position</returns>
		virtual double getY() { return yPos; };
	protected:
		Entity();

		double xPos;
		double yPos;

	private:
		Entity(const Entity&) = delete;
		const Entity& operator=(const Entity&) = delete;
	};
}

#endif