#include "pause_module.h"

PauseModule::PauseModule() {
	updateOn = { "paused" };
	drawOn = { "paused" };
	eventOn = { "paused"};

	pauseImg = wind::Image("../assets/paused.png");
}

void PauseModule::handleEvents(SDL_Event* current_event) {

}

void PauseModule::update(double dt) {
	if (wind::turbine.keyDown("w")) {
		std::cout << "Game is paused" << dt << "\n";
	}

	if (wind::turbine.keyDown("t")) {
		wind::state.setCurrentState("play");
	}
}

void PauseModule::draw() {
	pauseImg.draw(0, 0, 255,255,255, 175);
	//std::cout << "State is drawing" << "\n";
}

void PauseModule::clean() {
	//std::cout << "State was cleaned" << "\n";
}