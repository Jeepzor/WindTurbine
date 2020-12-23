#include "pause_module.h"

PauseModule::PauseModule() {
	updateOn = { "paused" };
	drawOn = { "paused" };
	eventOn = { "paused"};
}

//void handleEvents();
void PauseModule::update(double dt) {
	if (wind::turbine.keyboardIsDown("w")) {
		std::cout << "[W] - hurr durr" << dt << "\n";
	}

	if (wind::turbine.keyboardIsDown("S")) {
		std::cout << "[S] - durr hurr" << "\n";
	}
}

void PauseModule::draw() {
	//std::cout << "State is drawing" << "\n";
}

void PauseModule::clean() {
	//std::cout << "State was cleaned" << "\n";
}

void PauseModule::handleEvents() {
	//std::cout << "State-events being managed" << "\n";
}