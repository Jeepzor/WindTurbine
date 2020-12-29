#include "pause_module.h"

PauseModule::PauseModule() {
	updateOn = { "paused" };
	drawOn = { "paused" };
	eventOn = { "paused"};

	pauseImg = new wind::Image("../assets/paused.png");
}

void PauseModule::keyPressed(std::string key) {
	if (key == "2") {
		wind::state.setCurrentState("play");
	}
}

void PauseModule::update(double dt) {
	if (wind::turbine.keyDown("W")) {
		std::cout << "Game is paused" << dt << "\n";
	}
}

void PauseModule::draw() {
	pauseImg->draw(0, 0, 255,255,255, 175);
	//std::cout << "State is drawing" << "\n";
}

void PauseModule::clean() {
	//std::cout << "State was cleaned" << "\n";
}