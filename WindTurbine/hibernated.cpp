#include "hibernated.h"

namespace wind {

	Hibernated::Hibernated(Target callback_target, double duration) {
		timer = duration;
		target = callback_target;
	}

	void Hibernated::update(double dt) {
		timer -= dt;
	}

	void Hibernated::checkDeath() {
		if (timer <= 0 && alive) {
			alive = false;
			target();
		}
	}
}