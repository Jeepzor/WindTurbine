#include "hibernate.h"

namespace wind {

	void Hibernate::it(Target target, double duration) {
		Hibernated* temp = new Hibernated(target, duration);
		queued.push_back(temp);
	}

	void Hibernate::update(double dt) {
		for (auto target : queued) {
			target->update(dt);
		}
	}

	void Hibernate::removeDead() {

	}

	Hibernate hibernate;
}