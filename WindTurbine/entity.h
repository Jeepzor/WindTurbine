#ifndef ENTITY_H
#define ENTITY_H
#include "wind_turbine.h"

namespace wind {
	class Entity
	{
	public:
		virtual ~Entity() {};
		virtual void draw() = 0;
		virtual void update(double dt) = 0;
		//Add function to get distance to another entity
		//Add function to get angle to another entity
	protected:
		Entity();

		double yPos;
		double xPos;

	private:
		Entity(const Entity&) = delete;
		const Entity& operator=(const Entity&) = delete;
	};

}

#endif