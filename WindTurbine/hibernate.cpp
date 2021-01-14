#include "hibernate.h"

namespace wind {

	void Hibernate::it(std::function<void()>  target, double duration) {
		Hibernated* temp = new Hibernated(target, duration);
		queued.push_back(temp);
	}

	void Hibernate::update(double dt) {
		for (auto target : queued) {
			target->update(dt);
		}

		removeDead();
	}

	void Hibernate::removeDead() {
		queued.erase(std::remove_if(queued.begin(), queued.end(), [](Hibernated* i) { return !(i->isAlive()); }), queued.end());
	}

	Hibernate hibernate;
}