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

		friend class Turbine; // The Turbine class handles updating Hibernate

		/// <summary>
		/// Set a function to be triggered after a specific duration.
		/// The function can be anonymous: 
		/// hibernate.it([=](int a) mutable {a = 5; }, 3);
		/// </summary>
		/// <param name="target"> = The function which will be called</param>
		/// <param name="duration"> = Duration</param>
		void it(std::function<void()>  target, double duration);
		

	private:
		void removeDead();
		void update(double dt);

		std::vector<Hibernated*> queued;
	};

	extern Hibernate hibernate;
}

#endif
