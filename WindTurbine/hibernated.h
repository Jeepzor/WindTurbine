#ifndef HIBERNATED_H
#define HIBERNATED_H

#include<vector>
#include<functional>

namespace wind {
	class Hibernated
	{
	public:
		//Hibernate handles the creation, updates and removes all instances of this class.
		friend class Hibernate; 


	private:
		Hibernated(std::function<void()>  target, double duration);
		void update(double dt);
		bool isAlive() { return alive; };
		void checkDeath();
		std::function<void()>  target;
		bool alive = true;
		double timer;
	};

}

#endif
