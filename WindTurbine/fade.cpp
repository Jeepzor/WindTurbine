#include "fade.h"
#include "graphics.h"

namespace wind {
	void Fade::out(double fade_duration) {
		targetAlpha = 0;
		duration = fade_duration;
		speed = 255 / duration;
	}
	
	void Fade::in(double fade_duration) {
		targetAlpha = 255;
		duration = fade_duration;
		speed = 255 / duration;
	}

	void Fade::update(double dt) {
		if (targetAlpha < alpha) {
			if (targetAlpha < alpha - speed * dt) {
				alpha -= speed * dt;
			}
			else {
				alpha = 0;
			}
		}
		else if (targetAlpha > alpha) {
			if (targetAlpha > alpha + speed * dt) {
				alpha += speed * dt;
			}
			else {
				alpha = 255;
			}
		}
	}

	void Fade::draw() {
		graphics.setColor(0, 0, 0, alpha);
		graphics.rectangle(0, 0, turbine.getWindowWidth(), turbine.getWindowHeight());
		graphics.clearColor();
	}

	Fade fade;
}