#ifndef HIBERNATE_H
#define HIBERNATE_H
#include<vector>
#include<functional>

#include "hibernated.h"

namespace wind {
	typedef std::function<void()> Target;

	class Hibernate
	{
	public:
		Hibernate() {};

		void it(Target target, double duration);
		
		void update(double dt);

	private:
		void removeDead();

		std::vector<Hibernated*> queued;
	};

	extern Hibernate hibernate;
}

#endif
