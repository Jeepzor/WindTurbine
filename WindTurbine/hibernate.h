#ifndef HIBERNATE_H
#define HIBERNATE_H

#include<vector>
#include<functional>

#include "hibernated.h"

namespace wind {

	class Hibernate
	{
	public:
		Hibernate() {};

		void it(std::function<void()>  target, double duration);
		
		void update(double dt);

	private:
		void removeDead();

		std::vector<Hibernated*> queued;
	};

	extern Hibernate hibernate;
}

#endif
