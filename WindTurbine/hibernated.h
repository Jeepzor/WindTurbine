#ifndef HIBERNATED_H
#define HIBERNATED_H

#include<vector>
#include<functional>

namespace wind {
	class Hibernated
	{
	public:
		Hibernated(std::function<void()>  target, double duration);

		bool isAlive() { return alive; };
		void update(double dt);

	private:
		void checkDeath();
		std::function<void()>  target;
		bool alive = true;
		double timer;
	};

}

#endif
