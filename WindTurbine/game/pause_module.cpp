#include <string>
#include "pause_module.h"


PauseModule::PauseModule() {
	updateOn = { "paused" };
	drawOn = { "paused" };
	eventOn = { "paused"};
	pauseImg = wind::Image::getInstance("game/assets/paused.png");
}

void PauseModule::keyPressed(std::string key) {
	if (key == "P") {
		if (!lock) {
			lock = !lock;
			wind::state.setCurrentState("play");
		}
		else {
			lock = !lock;
		}
	}
}

void PauseModule::update(double dt) {
	if (wind::turbine.keyDown("W")) {
		std::cout << "Game is paused" << dt << "\n";
	}
}

void PauseModule::draw() {
	wind::graphics.setColor(255, 255, 255, 155);
	pauseImg->draw(0, 0);
	//std::cout << "State is drawing" << "\n";
}

void PauseModule::clean() {
	//std::cout << "State was cleaned" << "\n";
}