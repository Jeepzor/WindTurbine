#include "hibernated.h"

namespace wind {

	Hibernated::Hibernated(std::function<void()> callback_target, double duration) {
		timer = duration;
		target = callback_target;
	}

	void Hibernated::update(double dt) {
		timer -= dt;
		checkDeath();
	}

	void Hibernated::checkDeath() {
		if (timer <= 0 && alive) {
			alive = false;
			target();
		}
	}
}