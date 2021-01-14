#ifndef HIBERNATED_H
#define HIBERNATED_H

#include<vector>
#include<functional>

namespace wind {
	typedef std::function<void()> Target;
	class Hibernated
	{
	public:

		Hibernated(Target target, double duration);

		void update(double dt);
		void checkDeath();

	private:
		Target target;
		bool alive = true;
		double timer;
	};

}

#endif
